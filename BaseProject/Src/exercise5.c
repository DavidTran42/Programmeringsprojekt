/*
 * exercise5.c
 *
 *  Created on: 8. jun. 2021
 *      Author: Marius Mainz
 */
/*
#include "exercise5.h"

void returnJoystick(){

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
				int j1=1;
			} else if (down) {
				int j2=1;
			} else if (left) {
				int j3=1;
			} else if (right) {
				int j4=1;
			} else if (center) {
				int j5=1;
			} else {
				j1=0; j2=0; j3=0; j4=0; j5=0;
			}
		}
*/
