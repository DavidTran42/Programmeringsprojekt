#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "Excellutex.h"
#define ESC 0x1B

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
	int16_t box_h = 45, box_w = 60;
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


void exercise6() {
	int mHz = 1;
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
	enableTimer();
	TIM2->ARR = 63999; // Set reload value for 64x10^3 HZ - 1 (1/100 second)
	setPrescaler(0); // prescale value
	TIM2->DIER |=0x0001; // Enable timer 2 interrupts

	// NVIC_SetPriority(TIM2_IRQn, priority);
	NVIC_EnableIRQ(TIM2_IRQn);

}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~0x0001;
}


void turnOn(GPIO_TypeDef *pin, uint32_t pinnum) {

	pin->OSPEEDR &= ~(0x00000003 << (pinnum * 2)); // Clear speed register
	pin->OSPEEDR |= (0x00000002 << (pinnum * 2)); // set speed register (0x01 - 10
	pin->OTYPER &= ~(0x0001 << (pinnum * 1)); // Clear output type register
	pin->OTYPER |= (0x0000 << (pinnum)); // Set output type register (0x00 -
	pin->MODER &= ~(0x00000003 << (pinnum * 2)); // Clear mode register
	pin->MODER |= (0x00000001 << (pinnum * 2)); // Set mode register (0x00 –

	pin->ODR &= ~(0x0001 << pinnum); //Set pin to low (turned on)

}

void turnOff(GPIO_TypeDef *pin, uint32_t pinnum) {

	pin->OSPEEDR &= ~(0x00000003 << (pinnum * 2)); // Clear speed register
	pin->OSPEEDR |= (0x00000002 << (pinnum * 2)); // set speed register (0x01 - 10
	pin->OTYPER &= ~(0x0001 << (pinnum * 1)); // Clear output type register
	pin->OTYPER |= (0x0000 << (pinnum)); // Set output type register (0x00 -
	pin->MODER &= ~(0x00000003 << (pinnum * 2)); // Clear mode register
	pin->MODER |= (0x00000001 << (pinnum * 2)); // Set mode register (0x00 –

	pin->ODR |= (0x0001 << pinnum); //Set pin to high (turned off)
}

void exercise5_2() {
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

int main(void) {
	uint16_t h;
	uint8_t i, j;
	i = 10;
	j = 3;
	uart_init(9600);
	// exercise1();
	//exercise2();
	//exercise3();
	//exercise4();
	//exercise5();
	//exercise5_2();
	//exercise6();

	while (1) {
	}
}

