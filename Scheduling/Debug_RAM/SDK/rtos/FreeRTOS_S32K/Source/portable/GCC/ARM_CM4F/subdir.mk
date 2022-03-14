################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


