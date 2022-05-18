################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../my_libraries/Battery_3_7/Battery_3_7.c 

OBJS += \
./my_libraries/Battery_3_7/Battery_3_7.o 

C_DEPS += \
./my_libraries/Battery_3_7/Battery_3_7.d 


# Each subdirectory must supply rules for building sources it contributes
my_libraries/Battery_3_7/%.o my_libraries/Battery_3_7/%.su: ../my_libraries/Battery_3_7/%.c my_libraries/Battery_3_7/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"F:/smart-cows/smart-cows-stm32/my_libraries/GPS/inc" -I"F:/smart-cows/smart-cows-stm32/my_libraries/Battery_3_7/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-my_libraries-2f-Battery_3_7

clean-my_libraries-2f-Battery_3_7:
	-$(RM) ./my_libraries/Battery_3_7/Battery_3_7.d ./my_libraries/Battery_3_7/Battery_3_7.o ./my_libraries/Battery_3_7/Battery_3_7.su

.PHONY: clean-my_libraries-2f-Battery_3_7

