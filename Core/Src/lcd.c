/*
 * lcd.c
 *
 *  Created on: Oct 30, 2023
 *      Author: luker
 */


#include "lcd.h"

void lcd_clearScreen(UART_HandleTypeDef * ptr_huart) {
// uint8_t clearDisplay [] = {0 x7C , 0 x2D };
// HAL_UART_Transmit ( ptr_huart , clearDisplay , sizeof ( clearDisplay ) , HAL_MAX_DELAY ) ;
	lcd_instruction(ptr_huart, LCD_CLR_DISP);
	lcd_instruction(ptr_huart, LCD_SETPOS);
}

void lcd_instruction (UART_HandleTypeDef * ptr_huart , uint8_t instruction) {
	uint8_t instruction_chars [] = {CNTRL_CHAR, instruction };
	HAL_UART_Transmit(ptr_huart, instruction_chars, sizeof(instruction_chars), HAL_MAX_DELAY);
}

void lcd_Cursor(UART_HandleTypeDef * ptr_huart , uint8_t cursor) {
	switch (cursor) {
		case 0:
			lcd_instruction(ptr_huart, LCD_ON_HIDE);
			break;
		case 1:
			lcd_instruction(ptr_huart, LCD_BLINK);
			break;
		case 2:
			lcd_instruction(ptr_huart, LCD_UNDERLINE);
			break;
		default:
			lcd_instruction(ptr_huart,  LCD_ON_HIDE);
			break;
	}
}

void lcd_cursorpos(UART_HandleTypeDef * ptr_huart, uint8_t cursor) {
	lcd_instruction(ptr_huart, LCD_SETPOS + cursor) ;
}

void lcd_write_c (UART_HandleTypeDef* ptr_huart, char* print_text) {
	HAL_UART_Transmit(ptr_huart, (unsigned char *) print_text, 20, HAL_MAX_DELAY);
	// HAL_UART_Transmit (ptr_huart, ( unsigned char *) mydisplay , 20 , HAL_MAX_DELAY ) ; // WATCH OUT !!!
}

void lcd_write_pos(UART_HandleTypeDef* ptr_huart, char* print_text, uint8_t lengthOfPrintText, uint8_t line, uint8_t pos) {
	int line_pos = 0;
	switch (line) {
		case 0:
			line_pos = pos;
			break ;
		case 1:
			line_pos = pos + 64;
			break ;
		case 2:
			line_pos = pos + 20;
			break ;
		case 3:
			line_pos = pos + 84;
			break ;
		default:
			line_pos = 0;
			break ;
	}
	lcd_cursorpos(ptr_huart, line_pos);
	HAL_UART_Transmit (ptr_huart, (unsigned char *) print_text, lengthOfPrintText, HAL_MAX_DELAY);
}
