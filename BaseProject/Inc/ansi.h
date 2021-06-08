/*
 * ansi.h
 *
 *  Created on: Jun 4, 2021
 *      Author: davidtran
 */

#ifndef ANSI_H_
#define ANSI_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#endif /* ANSI_H_ */

typedef struct vector_t v;

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char text[], uint8_t style);
void window2(uint16_t x1, uint16_t y1, uint16_t x2 , uint16_t y2, char title[],int style);
void box(int16_t x1,int16_t y1,int16_t x2,int16_t y2, int16_t style);
void boxWithinBox(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t n);


void repeat(int c, int count);

void printFix(int32_t i);
int32_t expand(int32_t i);
int32_t calcSin(int32_t i);
