################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/userlibs/port/config_port.c 

OBJS += \
./src/userlibs/port/config_port.o 

C_DEPS += \
./src/userlibs/port/config_port.d 


# Each subdirectory must supply rules for building sources it contributes
src/userlibs/port/%.o: ../src/userlibs/port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/userlibs/port/config_port.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


