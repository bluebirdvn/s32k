################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/userlibs/adc/config_adc.c 

OBJS += \
./src/userlibs/adc/config_adc.o 

C_DEPS += \
./src/userlibs/adc/config_adc.d 


# Each subdirectory must supply rules for building sources it contributes
src/userlibs/adc/%.o: ../src/userlibs/adc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/userlibs/adc/config_adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


