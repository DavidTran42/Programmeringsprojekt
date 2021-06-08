#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "Excellutex.h"
#define ESC 0x1B

typedef struct {
	int32_t x, y;
} vector_t;

typedef struct ball{
	vector_t position;
	vector_t velocity;
} ball;

int16_t SubSubRotine(uint16_t e, uint16_t f){
	int16_t g = 0;
	uint16_t count = 0;

	do{
		g = g + e;
		count++;
	}while(count < f);

	return g;
}


int16_t SubRotine(int8_t a, int8_t b){
	int8_t c = 0;
	int16_t d;

	for(uint8_t i = 0;i < b; i++){
		d = c;
		c = SubSubRotine(a, d);
	}
	return c;
}

void exercise1() {
	printf("_______________________________________________________________________________\n");
	printf("|=============================== Debugger task ===============================|\n");
	printf("-------------------------------------------------------------------------------\n\n");
	printf("User : Mark Gudmund Maja\n\n");
	blink(1);
	printf("Hello and welcome to this debugger task.\n"
			"In this task you need to control the chips debugger to stop at certain points, \n");
	blink(0);
	underline(1);
	printf("in the code so you can produce certain screenshots and identify the values of\n"
			"a number of variables.\n");
	underline(0);
	inverse(1);
	printf("It is not the intent that you have to change the code nor is it allowed.\n"
			"But you will have to answer some questions explained why some number are as\n"
			"there are.\n\n");
	inverse(0);
	printf("|123456789|123456789|123456789|123456789|123456789|123456789|123456789|\n");
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

	printf("_______________________________________________________________________________\n");
	clreol();
	clreol();
	gotoxy(0,0);
	clreol();
	clrscr();
}

void exercise2() {
	color(6,0);//(Foreground,Background)
	clrscr(); // clear screen
	window2(1,1,20,20,"Window title",2);//(x1,y1,x2,y2,title,style)
}

void exercise3() {
	printFix(calcSin(0));
	printf("\n");
	printFix(calcSin(45));
	printf("\n");
	printFix(calcSin(-78));
	printf("\n");
	printFix(calcSin(649));
	printf("\n");

	printFix(calcCos(0));
	printf("\n");
	printFix(calcCos(45));
	printf("\n");
	printFix(calcCos(-78));
	printf("\n");
	printFix(calcCos(649));
	printf("\n");

	vector_t v1, v2, v3, v4;
	v1.x = 1, v1.y = 2;
	v2.x = 6, v2.y = 4;
	v3.x = -4, v3.y = -4;
	v4.x = -4, v4.y = 2;

	rotateVector(&v1, 180);
	rotateVector(&v2,-10);
	rotateVector(&v3,900);
	rotateVector(&v4,-35);

	printVector(&v1);
	printVector(&v2);
	printVector(&v3);
	printVector(&v4);
}

void exercise4(){
	int count = 0;
	int16_t box_h = 45, box_w = 60;
	color(6,0);//(Foreground,Background)
	clrscr(); // clear screen
	printf("%c[?25l",ESC);
	box(1,1,box_w,box_h,2);
	boxWithinBox(1,1,box_w,box_h,count);

	struct ball ball1;
	ball1.position.x = 2, ball1.position.y = 2;
	ball1.velocity.x = 1, ball1.velocity.y = 1;
	printBall(&ball1.position);
	while(1){
	boxWithinBox(1,1,box_w,box_h,count);
	gotoxy(ball1.position.x,ball1.position.y);
	printf(" ");
	updatePos(&ball1.position, &ball1.velocity);
	printBall(&ball1.position);
	count = checkCollision(&ball1.position, &ball1.velocity, box_h-2, box_w-2, count);
	}
}

int main(void)
{
	uint16_t h;
	uint8_t i,j;
	i = 10;
	j = 3;
	uart_init(9600);
	// exercise1();
	// exercise2();

	exercise4();

	while(1){}
}

