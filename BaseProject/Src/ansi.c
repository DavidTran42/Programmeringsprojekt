#define ESC 0x1B
#include "ansi.h"
#include "Excellutex.h"
#include "charset.h"
#include "30010_io.h"

void fgcolor(uint8_t foreground) {
	/*  Value      foreground     Value     foreground
	 ------------------------------------------------
	 0        Black            8       Dark Gray
	 1        Red              9       Light Red
	 2        Green           10       Light Green
	 3        Brown           11       Yellow
	 4        Blue            12       Light Blue
	 5        Purple          13       Light Purple
	 6        Cyan            14       Light Cyan
	 7        Light Gray      15       White
	 */
	uint8_t type = 22;             // normal text
	if (foreground > 7) {
		type = 1;                // bold text
		foreground -= 8;
	}
	printf("%c[%d;%dm", ESC, type, foreground + 30);
}

void bgcolor(uint8_t background) {
	/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
	 Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
	 The designers of HyperTerminal, however, preferred black text on white background, which is why
	 the colors are initially like that, but when the background color is first changed there is no
	 way comming back.

	 Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

	 Value      Color
	 ------------------
	 0        Black
	 1        Red
	 2        Green
	 3        Brown
	 4        Blue
	 5        Purple
	 6        Cyan
	 7        Gray
	 */
	printf("%c[%dm", ESC, background + 40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
	uint8_t type = 22;             // normal text
	if (foreground > 7) {
		type = 1;                // bold text
		foreground -= 8;
	}
	printf("%c[%d;%d;%dm", ESC, type, foreground + 30, background + 40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
	printf("%c[m", ESC);
}

void clrscr() {
	printf("%c[2J%c[H", ESC, ESC);
}

void clreol() {
	printf("%c[1F%c[2K", ESC, ESC);
}

void gotoxy(uint16_t x, uint16_t y) {
	printf("%c[%d;%dH", ESC, y, x); // line = y, column = x
}

void underline(uint8_t on) {
	if (on % 2 == 0) { // False
		printf("%c[24m", ESC);
	} else { // True
		printf("%c[4m", ESC);
	}
}

void blink(uint8_t on) {
	if (on % 2 == 0) { // False
		printf("%c[25m", ESC);
	} else { // True
		printf("%c[5m", ESC);
	}
}

void inverse(uint8_t on) {
	if (on % 2 == 0) { // False
		printf("%c[27m", ESC);
	} else { // True
		printf("%c[7m", ESC);
	}
}

void repeat(int c, int count) {
	for (int i = 0; i < count; i++)
		printf("%c", c);
}

void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char text[],
		uint8_t style) {
	// Set style
	printf(("%c[%dm"), ESC);

	if (x1 == 0) {
		x1 = 1;
		x2 = x2 + 1;
	}
	if (y1 == 0) {
		y1 = 1;
		y2 = y2 + 1;
	}
	gotoxy(x1, y1);
	printf("\u250C");
	inverse(1);
	printf(" %s", text);
	repeat(32, (x2 - x1 - strlen(text) - 3));
	inverse(0);
	printf("\u2510\n");
	for (int i = y1 + 1; i < y2 - 1; i++) {
		gotoxy(x1, i);
		printf("\u2502");
		repeat(' ', x2 - 2 - x1);
		printf("\u2502\n");
	}
	gotoxy(x1, y2 - 1);
	printf("\u2514");
	repeat('-', x2 - x1 - 2);
	printf("\u2518\n");
}

// window 2
void window2(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, char title[],
		int style) {
	if (style == 1) {
		gotoxy(x1, y1);
		printf("%c%c%c", 201, 205, 186);
		inverse(1);
		printf(" %s", title);
		for (int i = 0; i < (x2 - x1 - strlen(title) - 7); i++) {
			printf(" ");
		}
		inverse(0);
		printf("%c%c%c", 186, 205, 187);
		for (int i = y1 + 1; i < y2 - 1; i++) {
			gotoxy(x1, i);
			printf("%c", 186);
			repeat(' ', x2 - 2 - x1);
			printf("%c\n", 186);
		}
		printf("%c", 200);
		repeat(205, (x2 - x1 - 2));
		printf("%c", 188);
	} else {
		gotoxy(x1, y1);
		printf("%c%c%c", 218, 196, 179);
		inverse(1);
		printf(" %s", title);
		for (int i = 0; i < (x2 - x1 - strlen(title) - 7); i++) {
			printf(" ");
		}
		inverse(0);
		printf("%c%c%c", 179, 196, 191);
		for (int i = y1 + 1; i < y2 - 1; i++) {
			gotoxy(x1, i);
			printf("%c", 179);
			repeat(' ', x2 - 2 - x1);
			printf("%c\n", 179);
		}
		printf("%c", 192);
		repeat(196, (x2 - x1 - 2));
		printf("%c", 217);
	}
}

void printFix(int32_t i) {
	// Prints a signed 16.16 fixed point number
	if ((i & 0x80000000) != 0) { // Handle negative numbers
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t) (i & 0xFFFF) >> 16);
	// Print a maximum of 4 decimal digits to avoid overflow
}

int32_t expand(int32_t i) {
	// Converts an 18.14 fixed point number to 16.16
	return i << 2;
}

int32_t calcSin(int32_t i) {
	i = (i * 512) / 360;
	if (i < 0) {
		int temp_i = -i;
		return -expand(SIN[temp_i]);
	} else if (i > 512) {
		i = i % 512;
	}
	return expand(SIN[i]);
}

int32_t calcCos(int32_t i) {
	i += 90;
	return calcSin(i);
}

typedef struct vector_t {
	int32_t x, y;
} vector_t;

typedef struct ball {
	vector_t position;
	vector_t velocity;
} ball;

void rotateVector(vector_t *v, int32_t degree) {
	int32_t tempX;
	tempX = v->x * calcCos(degree) - v->y * calcSin(degree);
	v->y = v->x * calcSin(degree) + v->y * calcCos(degree);
	v->x = tempX;
}

void updatePos(vector_t *pos, vector_t *vel) {
	pos->x += vel->x;
	pos->y += vel->y;
}

int32_t checkCollision(vector_t *pos, vector_t *vel, int32_t box_height,
		int32_t box_width, int count) {
	// Check if it his the wall
	if (pos->x <= 2 || pos->x >= box_width) {
		vel->x = -vel->x;
		count++;
	} else if (pos->y <= 2 || pos->y >= box_height) {
		vel->y = -vel->y;
		count++;
	}
	if (count > 999) {
		count = 0;
	}
	return count;
}

void printBall(vector_t *position) {
	gotoxy(position->x, position->y);
	printf("o");
}

void printVector(vector_t *v) {
	printf("(");
	printFix(v->x);
	printf(",");
	printFix(v->y);
	printf(")");
	printf("\n");
}

void box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t style) {
	//Greate outside walls with style 2
	if (style != 1) {
		gotoxy(x1, y1);
		printf("%c", 201);
		repeat(205, (x2 - x1 - 2));
		printf("%c", 187);
		for (int i = y1 + 1; i < y2 - 1; i++) {
			gotoxy(x1, i);
			printf("%c", 186);
			gotoxy(x2-x1,i);
			printf("%c\n", 186);
		}
		printf("%c", 200);
		repeat(205, (x2 - x1 - 2));
		printf("%c", 188);
	}
	// Greate outside walls with style 1
	else {
		gotoxy(x1, y1);
		printf("%c", 218);
		repeat(196, (x2 - x1 - 2));
		printf("%c", 191);
		for (int i = y1 + 1; i < y2 - 1; i++) {
			gotoxy(x1, i);
			printf("%c", 179);
			gotoxy(x2-x1,i);
			printf("%c\n", 179);
		}
		printf("%c", 192);
		repeat(196, (x2 - x1 - 2));
		printf("%c", 217);
	}
}

void boxWithinBox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t n) {
	//Greate the inside box
	gotoxy((((x2 - x1) / 2) - (11) / 2), (((y2 - y1) / 2) - (5 / 2) + 1));
	printf("%c", 201);
	repeat(205, 11 - 2);
	printf("%c", 187);
	// Printer text og midste af boxen
	gotoxy(((x2 - x1) / 2) - (11 / 2), ((y2 - y1) / 2) - (5 / 2) + 2);
	printf("%c", 186);
	inverse(1);
	if (n < 10) {
		printf("Hits: %d  ", n);
		inverse(0);
		printf("%c\n", 186);
	} else if (10 <= n && n < 100) {
		printf("Hits: %d ", n);
		inverse(0);
		printf("%c\n", 186);
	} else if (n >= 100) {
		printf("Hits: %d", n);
		inverse(0);
		printf("%c\n", 186);
	}
	//Printer bunden af boxen
	gotoxy(((x2 - x1) / 2) - (11 / 2), (((y2 - y1) / 2) - (5 / 2) + 3));
	printf("%c", 200);
	repeat(205, (11 - 2));
	printf("%c", 188);
}

void turnOn(GPIO_TypeDef *pin, uint32_t pinnum) {

	pin->OSPEEDR &= ~(0x00000003 << (pinnum * 2)); // Clear speed register
	pin->OSPEEDR |= (0x00000002 << (pinnum * 2)); // set speed register (0x01 - 10
	pin->OTYPER &= ~(0x0001 << (pinnum * 1)); // Clear output type register
	pin->OTYPER |= (0x0000 << (pinnum)); // Set output type register (0x00 -
	pin->MODER &= ~(0x00000003 << (pinnum * 2)); // Clear mode register
	pin->MODER |= (0x00000001 << (pinnum * 2)); // Set mode register (0x00 ???

	pin->ODR &= ~(0x0001 << pinnum); //Set pin to low (turned on)

}

void turnOff(GPIO_TypeDef *pin, uint32_t pinnum) {

	pin->OSPEEDR &= ~(0x00000003 << (pinnum * 2)); // Clear speed register
	pin->OSPEEDR |= (0x00000002 << (pinnum * 2)); // set speed register (0x01 - 10
	pin->OTYPER &= ~(0x0001 << (pinnum * 1)); // Clear output type register
	pin->OTYPER |= (0x0000 << (pinnum)); // Set output type register (0x00 -
	pin->MODER &= ~(0x00000003 << (pinnum * 2)); // Clear mode register
	pin->MODER |= (0x00000001 << (pinnum * 2)); // Set mode register (0x00 ???

	pin->ODR |= (0x0001 << pinnum); //Set pin to high (turned off)
}

void exercise5_2() {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 ???
	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	uint16_t right = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 ???
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
	uint16_t up = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 ???
	GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -
	uint16_t center = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5

	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 ???
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -
	uint16_t left = GPIOC->IDR & (0x0001 << 1); //Read from pin PC5

	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 ???
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	uint16_t down = GPIOB->IDR & (0x0001 << 0); //Read from pin PA4

	printf("%c[?25l", ESC); //Hiding curser

	while (1) {
		right = GPIOC->IDR & (0x0001 << 0);
		up = GPIOA->IDR & (0x0001 << 4);
		center = GPIOB->IDR & (0x0001 << 5);
		left = GPIOC->IDR & (0x0001 << 1);
		down = GPIOB->IDR & (0x0001 << 0);

		gotoxy(0, 0);

		if (up) {
			printf("0000001");
			turnOn(GPIOA, 9);
			turnOff(GPIOB, 4);
			turnOff(GPIOC, 7);
		} else if (down) {
			printf("0000010");
			turnOff(GPIOA, 9);
			turnOn(GPIOB, 4);
			turnOff(GPIOC, 7);
		} else if (left) {
			printf("0000100");
			turnOff(GPIOA, 9);
			turnOff(GPIOB, 4);
			turnOn(GPIOC, 7);
		} else if (right) {
			printf("0001000");
			turnOn(GPIOA, 9);
			turnOn(GPIOB, 4);
			turnOff(GPIOC, 7);
		} else if (center) {
			printf("0010000");
			turnOff(GPIOA, 9);
			turnOn(GPIOB, 4);
			turnOn(GPIOC, 7);
		} else {
			printf("0000000");
			turnOn(GPIOA, 9);
			turnOff(GPIOB, 4);
			turnOn(GPIOC, 7);
		}
	}
}

void pattern(uint8_t *disp) {
	lcd_init();

	uint8_t buffer[512] = { 0 }; //creating graphics buffer
	memset(buffer, disp, 512);
	lcd_push_buffer(buffer);
}



void lcd_write_string(uint8_t buffer[512], char *slice, uint8_t line) {

	uint8_t location = 0;

	for (int i = 0; i < strlen(slice); i++) {
		for (int j = 0; j < 5; j++) {
			buffer[location + j + (line - 1) * 128] = character_data[slice[i]- 32][j];
			buffer[location + j + (line - 1) * 128] = character_data[slice[i] - 32][j];
		}
		location += 5;
	}
	lcd_push_buffer(buffer);
	lcd_update(buffer,2);
}


