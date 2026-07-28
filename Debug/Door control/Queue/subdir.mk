################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Door\ control/Queue/Queue.c 

OBJS += \
./Door\ control/Queue/Queue.o 

C_DEPS += \
./Door\ control/Queue/Queue.d 


# Each subdirectory must supply rules for building sources it contributes
Door\ control/Queue/Queue.o: ../Door\ control/Queue/Queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"Door control/Queue/Queue.d" -MT"Door\ control/Queue/Queue.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


