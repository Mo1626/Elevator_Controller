/*


* Buzz_int.h
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#ifndef BUZZ_INT_H_
#define BUZZ_INT_H_

void Buzzer_vidInit(void);
void Buzzer_vidKeyClick(void);      /* صوت ضغطة الزرار القصيرة */
void Buzzer_vidErrorKey(void);      /* صوت الخطأ (زرار غير مسموح أو الباب مفتوح) */
void Buzzer_vidArrivalChime(void);  /* نغمة الوصول للدور المطلوب */
void Buzzer_vidEstop(void);         /* نغمة الطوارئ المستمرة */

#endif
