/*
 * ADC_int.h
 *
 *  Created on: Jul 22, 2026
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

void ADC_vidInit(void);

//for trial only 
u8 ADC_u8GetPolling(u8 u8AdcChannel);
//for trial only 



// assignment

u16 ADC_u8GetLoadPercentage(u8 Channel);

void ADC_vidSelectChannel(u8 u8AdcChannel);

void ADC_vidInit(void);

u8 ADC_u8GetHighRead(void);

u16 ADC_u16GetRead(void);

void ADC_vidSelectAutoTrigger(u8 u8TriggerSource);

void ADC_vidEnable(void);
void ADC_vidDisable(void);

void ADC_vidEnableInterrupt(void);
void ADC_vidDisableInterrupt(void);

void ADC_vidSetCallback(void(*pfunAppFunction)(void));

#endif /* MCAL_ADC_ADC_INT_H_ */
