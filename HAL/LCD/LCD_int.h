/*

* LCD_int.h
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#include "../../MCAL/ADC/primitiveTypes.h"

#ifndef LCD_INT_H_
#define LCD_INT_H_

void LCD_vidInit(void);
void LCD_vidSendData(u8 u8Data);
void LCD_vidSendCommand(u8 u8Command);

void LCD_vidSendString(const char* pcString);

void LCD_vidSetPositionXY(u8 u8X , u8 u8Y);
void LCD_vidSendIntegarNumber(s32 s32Number);
void LCD_vidSendFloatNumber(float fNumber);
void LCD_vidSendPattern(u8 * pu8Patterns, u8 u8PatternCount , u8 u8X, u8 u8Y, u8 u8DisplayDirection);

#endif /* LCD_INT_H_ */
