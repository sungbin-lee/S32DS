################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/platform/devices/S32K148/startup/gcc/startup_S32K148.S 

OBJS += \
./Project_Settings/Startup_Code/startup_S32K148.o 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/startup_S32K148.o: F:/NXP/S32DS_ARM_v2.2/S32DS/software/S32SDK_S32K1xx_RTM_3.0.0/platform/devices/S32K148/startup/gcc/startup_S32K148.S
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@Project_Settings/Startup_Code/Startup_S32K148.args" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


