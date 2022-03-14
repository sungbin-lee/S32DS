################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/croutine.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/event_groups.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/list.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/queue.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/stream_buffer.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/tasks.c \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/timers.c 

OBJS += \
./SDK/rtos/FreeRTOS_S32K/Source/croutine.o \
./SDK/rtos/FreeRTOS_S32K/Source/event_groups.o \
./SDK/rtos/FreeRTOS_S32K/Source/list.o \
./SDK/rtos/FreeRTOS_S32K/Source/queue.o \
./SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.o \
./SDK/rtos/FreeRTOS_S32K/Source/tasks.o \
./SDK/rtos/FreeRTOS_S32K/Source/timers.o 

C_DEPS += \
./SDK/rtos/FreeRTOS_S32K/Source/croutine.d \
./SDK/rtos/FreeRTOS_S32K/Source/event_groups.d \
./SDK/rtos/FreeRTOS_S32K/Source/list.d \
./SDK/rtos/FreeRTOS_S32K/Source/queue.d \
./SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.d \
./SDK/rtos/FreeRTOS_S32K/Source/tasks.d \
./SDK/rtos/FreeRTOS_S32K/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/rtos/FreeRTOS_S32K/Source/croutine.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/croutine.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/event_groups.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/event_groups.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/list.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/list.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/queue.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/stream_buffer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/tasks.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/rtos/FreeRTOS_S32K/Source/timers.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/rtos/FreeRTOS_S32K/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


