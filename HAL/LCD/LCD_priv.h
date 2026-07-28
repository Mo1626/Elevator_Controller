/*

* LCD_priv.h
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

static void vidWriteNLatch(u8 u8Byte);

#define LCD_8_BIT                    (76U)
#define LCD_4_BIT                    (32U)

#define PATTERN0                     (0X40)
#define PATTERN1                     (0X48)
#define PATTERN2                     (0X50)
#define PATTERN3                     (0X58)
#define PATTERN4                     (0X60)
#define PATTERN5                     (0X68)
#define PATTERN6                     (0X70)
#define PATTERN7                     (0X78)

#define LCD_EIGHT_BIT_FUNCTION_SET    (0x38U)
#define LCD_FOUR_BIT_FUNCTION_SET     (0x28U)
#define LCD_DISPLAY_ON_OFF            (0x0FU)
#define LCD_CLEAR_DISPLAY             (0x01U)
#define LCD_ENTRY_MODE_SET            (0x06U)

#endif /* LCD_PRIV_H_ */
