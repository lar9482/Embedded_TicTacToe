/*
 * lcd.h
 *
 *  Created on: Oct 30, 2023
 *      Author: luker
 */

#ifndef SRC_LCD_H_
#define SRC_LCD_H_


#include "stm32f4xx_hal.h"
#include <string.h>
#include "main.h"

#define CNTRL_CHAR 0xFE

#define LCD_CLR_DISP 0x01
// # define LCD_CLR_DISP 0x2D
#define LCD_MV_RIGHT 0x14
#define LCD_MV_LEFT 0x10
#define LCD_SCRL_RIGHT 0x1C
#define LCD_SCRL_LEFT 0x18
#define LCD_ON_HIDE 0x0C
#define LCD_OFF 0x08
#define LCD_UNDERLINE 0x0E
#define LCD_BLINK 0x0D
#define LCD_SETPOS 0x80

#define CURSOR_OFF 0
#define CURSOR_BLINK 1
#define CURSOR_UNDER 2

#define HAL_MAX_DELAY 100

void lcd_clearScreen(UART_HandleTypeDef* ptr_huart ) ;
void lcd_instruction(UART_HandleTypeDef* ptr_huart, uint8_t instruction);
void lcd_Cursor(UART_HandleTypeDef* ptr_huart, uint8_t cursor);
void lcd_write_c(UART_HandleTypeDef* ptr_huart, char* print_text);
void lcd_write_pos(UART_HandleTypeDef* ptr_huart, char* print_text, uint8_t lengthOfPrintText, uint8_t line, uint8_t pos);


#endif /* SRC_LCD_H_ */
