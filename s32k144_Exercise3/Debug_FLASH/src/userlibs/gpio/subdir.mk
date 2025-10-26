################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/userlibs/gpio/config_gpio.c 

OBJS += \
./src/userlibs/gpio/config_gpio.o 

C_DEPS += \
./src/userlibs/gpio/config_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/userlibs/gpio/%.o: ../src/userlibs/gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/userlibs/gpio/config_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


