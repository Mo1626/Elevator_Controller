################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Door\ control/Door/Door.c 

OBJS += \
./Door\ control/Door/Door.o 

C_DEPS += \
./Door\ control/Door/Door.d 


# Each subdirectory must supply rules for building sources it contributes
Door\ control/Door/Door.o: ../Door\ control/Door/Door.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"Door control/Door/Door.d" -MT"Door\ control/Door/Door.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


