/*

* LCD_config.h
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/********************************************************/
/**** LCD Mode configuration "LCD_8_BIT - LCD_4_BIT" ****/
/********************************************************/
#define LCD_MODE                    LCD_8_BIT

/********************************************************/
/**** LCD Control pins configuration "RS - R/W - EN" ****/
/********************************************************/
#define LCD_RS_PIN                  PB7
#define LCD_RW_PIN                  PB6
#define LCD_EN_PIN                  PB5

/********************************************************/
/**** LCD Data pins config "D7,D6,D5,D4,D3,D2,D1,D0" ****/
/********************************************************/
#define LCD_D7_PIN                  PA5
#define LCD_D6_PIN                  PA6
#define LCD_D5_PIN                  PA7
#define LCD_D4_PIN                  PB0
#define LCD_D3_PIN                  PB1
#define LCD_D2_PIN                  PB2
#define LCD_D1_PIN                  PB3
#define LCD_D0_PIN                  PB4

#endif /* LCD_CONFIG_H_ */
