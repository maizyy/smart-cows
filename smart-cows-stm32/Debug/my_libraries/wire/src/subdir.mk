################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../my_libraries/wire/src/wire.c 

OBJS += \
./my_libraries/wire/src/wire.o 

C_DEPS += \
./my_libraries/wire/src/wire.d 


# Each subdirectory must supply rules for building sources it contributes
my_libraries/wire/src/%.o my_libraries/wire/src/%.su: ../my_libraries/wire/src/%.c my_libraries/wire/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"F:/smart-cows/smart-cows-stm32/my_libraries/GPS/inc" -I"F:/smart-cows/smart-cows-stm32/my_libraries/Battery_3_7/inc" -I"F:/smart-cows/smart-cows-stm32/my_libraries/wire/inc" -I"F:/smart-cows/smart-cows-stm32/my_libraries/ds18b20/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-my_libraries-2f-wire-2f-src

clean-my_libraries-2f-wire-2f-src:
	-$(RM) ./my_libraries/wire/src/wire.d ./my_libraries/wire/src/wire.o ./my_libraries/wire/src/wire.su

.PHONY: clean-my_libraries-2f-wire-2f-src

