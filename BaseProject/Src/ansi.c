#define ESC 0x1B
#include "ansi.h"
#include "Excellutex.h"

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
  printf("%c[%d;%dm", ESC, type, foreground+30);
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
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
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

void gotoxy(uint8_t x, uint8_t y) {
	printf("%c[%d;%dH",ESC,y,x); // line = y, column = x
}

void underline(uint8_t on) {
	if (on%2==0) { // False
		printf("%c[24m",ESC);
	} else { // True
		printf("%c[4m",ESC);
	}
}

void blink(uint8_t on) {
	if (on%2==0) { // False
		printf("%c[25m",ESC);
	} else { // True
		printf("%c[5m",ESC);
	}
}

void inverse(uint8_t on) {
	if (on%2==0) { // False
		printf("%c[27m",ESC);
	} else { // True
		printf("%c[7m",ESC);
	}
}

void repeat(int c, int count) {
	for (int i = 0; i<count;i++)
		printf("%c", c);
}


void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char text[], uint8_t style) {
	// Set style
	printf(("%c[%dm"),ESC);

	if (x1 == 0) {
		x1 = 1;
		x2 = x2+1;
	}
	if (y1 == 0) {
		y1 = 1;
		y2 = y2+1;
	}
	gotoxy(x1,y1);
	printf("\u250C");
	inverse(1);
	printf(" %s", text);
	repeat(32, (x2-x1-strlen(text)-3));
	inverse(0);
	printf("\u2510\n");
	for(int i = y1+1; i < y2-1; i++){
		gotoxy(x1,i);
		printf("\u2502");
		repeat(' ', x2-2-x1);
		printf("\u2502\n");
	}
	gotoxy(x1,y2-1);
	printf("\u2514");
	repeat('-',x2-x1-2);
	printf("\u2518\n");
}

void printFix(int32_t i) {
	// Prints a signed 16.16 fixed point number
	if ((i & 0x80000000) != 0) { // Handle negative numbers
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	// Print a maximum of 4 decimal digits to avoid overflow
}

int32_t expand(int32_t i) {
	// Converts an 18.14 fixed point number to 16.16
	return i << 2;
}

int32_t calcSin(int32_t i) {
	i = (i*512)/360;
	if (i < 0) {
		int temp_i = -i;
		return -expand(SIN[temp_i]);
	} else if (i > 512) {
		i = i%512;
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

void rotateVector(vector_t *v, int32_t degree) {
	int32_t tempX;
	tempX = v->x * calcCos(degree) - v->y * calcSin(degree);
	v->y = v->x * calcSin(degree) + v->y * calcCos(degree);
	v->x = tempX;
}

void printVector(vector_t *v) {
	printf("(");
	printFix(v->x);
	printf(",");
	printFix(v->y);
	printf(")");
	printf("\n");
}


