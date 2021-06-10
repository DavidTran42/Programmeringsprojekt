#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "Excellutex.h"
#include "charset.h"
#include <string.h>

#define ESC 0x1B

typedef struct time {
	volatile int8_t hour, min, sec, sec100;
} time;

struct time timer;

typedef struct {
	int32_t x, y;
} vector_t;

typedef struct ball {
	vector_t position;
	vector_t velocity;
} ball;

int16_t SubSubRotine(uint16_t e, uint16_t f) {
	int16_t g = 0;
	uint16_t count = 0;

	do {
		g = g + e;
		count++;
	} while (count < f);

	return g;
}

int16_t SubRotine(int8_t a, int8_t b) {
	int8_t c = 0;
	int16_t d;

	for (uint8_t i = 0; i < b; i++) {
		d = c;
		c = SubSubRotine(a, d);
	}
	return c;
}

void exercise1() {
	printf(
			"_______________________________________________________________________________\n");
	printf(
			"|=============================== Debugger task ===============================|\n");
	printf(
			"-------------------------------------------------------------------------------\n\n");
	printf("User : Mark Gudmund Maja\n\n");
	blink(1);
	printf(
			"Hello and welcome to this debugger task.\n"
					"In this task you need to control the chips debugger to stop at certain points, \n");
	blink(0);
	underline(1);
	printf(
			"in the code so you can produce certain screenshots and identify the values of\n"
					"a number of variables.\n");
	underline(0);
	inverse(1);
	printf(
			"It is not the intent that you have to change the code nor is it allowed.\n"
					"But you will have to answer some questions explained why some number are as\n"
					"there are.\n\n");
	inverse(0);
	printf(
			"|123456789|123456789|123456789|123456789|123456789|123456789|123456789|\n");
	printf("|*    ");
	printf("*   |   ");
	printf("*     |     ");
	printf("*   |  ");
	printf("*      |    ");
	printf("*    |  ");
	printf("*      |      ");
	printf("*  |\n");
	printf("|********* *********|");
	printf("********* ********* *********|");
	printf("********* *********|\n\n");

	// h = SubRotine(j, i);

	printf(
			"_______________________________________________________________________________\n");
	clreol();
	clreol();
	gotoxy(0, 0);
	clreol();
	clrscr();
}

void exercise2() {
	color(6, 0); //(Foreground,Background)
	clrscr(); // clear screen
	window(0, 0, 20, 10, "Window Title", 1);
	window2(1, 1, 20, 20, "Window title", 2); //(x1,y1,x2,y2,title,style)

}

void exercise3() {
	printf("sin(0deg): ");
	printFix(calcSin(0));
	printf("\n sin(45deg): ");
	printFix(calcSin(45));
	printf("\n sin(-78deg): ");
	printFix(calcSin(-78));
	printf("\n sin(649deg): ");
	printFix(calcSin(649));
	printf("\n cos(0deg): ");

	printFix(calcCos(0));
	printf("\n cos(45deg): ");
	printFix(calcCos(45));
	printf("\n cos(-78deg): ");
	printFix(calcCos(-78));
	printf("\n cos(649deg): ");
	printFix(calcCos(649));
	printf("\n\n");

	vector_t v1, v2, v3, v4;
	v1.x = 1, v1.y = 2;
	v2.x = 6, v2.y = 4;
	v3.x = -4, v3.y = -4;
	v4.x = -4, v4.y = 2;

	rotateVector(&v1, 180);
	rotateVector(&v2, -10);
	rotateVector(&v3, 900);
	rotateVector(&v4, -35);
	printf("rotateVector((1,2), 180):\n");
	printVector(&v1);
	printf("rotateVector((6,4), -10):\n");
	printVector(&v2);
	printf("rotateVector((-4,-4), 900):\n");
	printVector(&v3);
	printf("rotateVector((-4,2), -35):\n");
	printVector(&v4);
}

void exercise4() {
	int count = 0;
	int16_t box_h = 20, box_w = 30;
	color(6, 0); //(Foreground,Background)
	clrscr(); // clear screen
	printf("%c[?25l", ESC);
	box(1, 1, box_w, box_h, 2);
	boxWithinBox(1, 1, box_w, box_h, count);

	struct ball ball1;
	ball1.position.x = 2, ball1.position.y = 2;
	ball1.velocity.x = 1, ball1.velocity.y = 1;

	printBall(&ball1.position);
	while (1) {
		boxWithinBox(1, 1, box_w, box_h, count);
		gotoxy(ball1.position.x, ball1.position.y);
		printf(" ");
		updatePos(&ball1.position, &ball1.velocity);
		printBall(&ball1.position);
		count = checkCollision(&ball1.position, &ball1.velocity, box_h - 2,
				box_w - 2, count);
	}
}

void exercise5() {
	color(6, 0); //(Foreground,Background)
	clrscr(); // clear screen
	//readJoystick()
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	uint16_t right = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
	uint16_t up = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 –
	GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -
	uint16_t center = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5

	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 –
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -
	uint16_t left = GPIOC->IDR & (0x0001 << 1); //Read from pin PC5

	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	uint16_t down = GPIOB->IDR & (0x0001 << 0); //Read from pin PA4

	printf("%c[?25l", ESC); //hiding curser

	while (1) {

		right = GPIOC->IDR & (0x0001 << 0);
		up = GPIOA->IDR & (0x0001 << 4);
		center = GPIOB->IDR & (0x0001 << 5);
		left = GPIOC->IDR & (0x0001 << 1);
		down = GPIOB->IDR & (0x0001 << 0);
		gotoxy(0, 0);

		if (up) {
			printf("0000001");
		} else if (down) {
			printf("0000010");
		} else if (left) {
			printf("0000100");
		} else if (right) {
			printf("0001000");
		} else if (center) {
			printf("0010000");
		} else {
			printf("0000000");
		}
	}
}

void enableTimer() {
	TIM2->CR1 |= 0x0001;
}

void disableTimer() {
	TIM2->CR1 &= 0x0000;
}

void setPrescaler(int32_t s) {
	TIM2->PSC = s;
}

void splitTime1() {
	printf("Split time 1: hour: %d, min: %d, sec: %d, sec100: %d\n", timer.hour,
			timer.min, timer.sec, timer.sec100);
}
void splitTime2() {
	printf("Split time 2: hour: %d, min: %d, sec: %d, sec100: %d\n", timer.hour,
			timer.min, timer.sec, timer.sec100);
}

void exercise6() {

	clrscr(); // clear screen
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
	enableTimer();
	TIM2->ARR = 639999; // Set reload value for 64x10^3 HZ - 1 (1/100 second)
	setPrescaler(0); // prescale value
	TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

	NVIC_SetPriority(TIM2_IRQn, 0); // Can be from 0-15
	NVIC_EnableIRQ(TIM2_IRQn);

	printf("%c[?25l", ESC);

		RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
		RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
		RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

		GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
		GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
		GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
		GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
		uint16_t right = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

		GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
		GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –
		GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
		GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
		uint16_t up = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

		GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
		GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 –
		GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
		GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -
		uint16_t center = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5

		GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
		GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 –
		GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
		GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -
		uint16_t left = GPIOC->IDR & (0x0001 << 1); //Read from pin PC5

		GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
		GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
		GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
		GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
		uint16_t down = GPIOB->IDR & (0x0001 << 0); //Read from pin PA4

		printf("%c[?25l", ESC); //hiding curser

		int c=0;


		while (1) {

			right = GPIOC->IDR & (0x0001 << 0);
			up = GPIOA->IDR & (0x0001 << 4);
			center = GPIOB->IDR & (0x0001 << 5);
			left = GPIOC->IDR & (0x0001 << 1);
			down = GPIOB->IDR & (0x0001 << 0);
			gotoxy(0, 0);

			if (center) {
				c++;
			}
			if (c==2){
				c=0;
			}

			if (down) {
				disableTimer();
				timer.hour=0; timer.min=0; timer.sec=0; timer.sec100=0;
			} else if (c==0) {
				enableTimer();
			} else if (c==1) {
				disableTimer();
			} else {
			}

		gotoxy(0,0);
		printf("hour: %d, min: %d, sec: %d, sec100: %d\n",timer.hour, timer.min, timer.sec, timer.sec100);

		if(left){
		splitTime1();
		}

		else if(right){
		printf("\n");
		splitTime2();
		}
		printf("\n\n");



	}
}

void exercise6_2() {
	int count = 0;
	char last_letter;
	char text[100] = "";

	clrscr(); // clear screen
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
	enableTimer();
	TIM2->ARR = 639999; // Set reload value for 64x10^3 HZ - 1 (1/100 second)
	setPrescaler(0); // prescale value
	TIM2->DIER |=0x0001; // Enable timer 2 interrupts

	NVIC_SetPriority(TIM2_IRQn, 0); // Can be from 0-15
	NVIC_EnableIRQ(TIM2_IRQn);

	// printf("%c[?25l", ESC);
	disableTimer();
	while(1) {

	gotoxy(0,0);
	printf("hour: %d, min: %d, sec: %d, sec100: %d\n",timer.hour, timer.min, timer.sec, timer.sec100);

	if (uart_get_count() > 0) {
		gotoxy(0,9);
		text[count] = uart_get_char();
		last_letter = text[count];
		printf("%s",text);
		count++;
	}

	if (last_letter == 0x0D) {
		if (strcmp("stop\r",text) == 0) {
			disableTimer();
		} else if (strcmp("start\r",text) == 0) {
			printf("gi");
			enableTimer();
		} else if (strcmp("split1\r",text) == 0) {
			gotoxy(0,2);
			splitTime1();
		} else if (strcmp("split2\r",text) == 0) {
			gotoxy(0,3);
			splitTime2();
		} else if (strcmp("reset\r",text) == 0) {
				disableTimer();
				timer.hour=0; timer.min=0; timer.sec=0; timer.sec100=0;
		} else if (strcmp("help",text) == 0) {

		} else {
			gotoxy(0,4);
			printf("start: start timer \n split1: stop timer 1 \n "
							"split2: stop timer 2 \n reset: reset timer \n"
							"help: guide to putty");
		}
		uart_clear();
		last_letter = '0';
		memset(text, 0, sizeof(text));
		count = 0;
		gotoxy(0,10);
		clreol();
		}
	}
}


void TIM2_IRQHandler(void) {

	timer.sec100++;

	if(timer.sec100 >= 100) {
		timer.sec++;
		timer.sec100 = 0;
	}

	if (timer.sec >= 60) {
		timer.min++;
		timer.sec = 0;
	}

	if (timer.min >= 60) {
		timer.hour++;
		timer.min = 0;
	}

	TIM2->SR &= ~0x0001;
}






void timerInterrupt() {
	enableTimer();
	uint8_t flag;
	while (1) {
		if (timer.sec++) {
			flag = 0;
			printf("%d", flag);
		} else {
			flag = 1;
			printf("%d", flag);
		}
	}
}

void lcd_update(uint8_t buffer[512], uint8_t line) {

		RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
		enableTimer();
		TIM2->ARR = 639999; // Set reload value for 64x10^3 HZ - 1 (1/100 second)
		setPrescaler(0); // prescale value
		TIM2->DIER |=0x0001; // Enable timer 2 interrupts

		NVIC_SetPriority(TIM2_IRQn, 0); // Can be from 0-15
		NVIC_EnableIRQ(TIM2_IRQn);
	while (1) {
		uint8_t temp = 1;
		if (timer.sec++) {
			temp = 0;
			printf("%d",temp);
		}
		if (temp == 1) {
			for (int i = 512; i > 0; i--) {
				buffer[i] = buffer[i + 1];
				if (i == 0) {
					buffer[511] = buffer[0];
				}
			}
			printf("%d", temp);
			lcd_push_buffer(buffer);
		}

	}

}



int main(void) {
	//uint16_t h;
	//uint8_t i, j;
	//i = 10;
	//j = 3;
	uart_init(9600);
	lcd_init();
	uint8_t buffer[512] = { 0 }; //creating graphics buffer
	// exercise1();
	//exercise2();
	//exercise3();
	//exercise4();
	//exercise5();
	//exercise5_2();
	// Exercise 6.2


	//exercise6.2();
	//char array[252];
	lcd_write_string(buffer, "abcdef ghijk 123", 1);
	lcd_update(buffer, 1);
	//timerInterrupt();
	//exercise6();
	//exercise5_2();

	//pattern(0x4D);
	//lcd_write_string(buffer, "Hej med jer", 2);
	//lcd_update(buffer, "abc", 3);
	// exercise6_2();

	//exercise6();

	while (1) {
	}
}

