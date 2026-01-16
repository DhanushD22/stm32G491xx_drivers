################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/002LED_Toggle.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/002LED_Toggle.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/002LED_Toggle.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_G491RE -DSTM32 -DSTM32G491RETx -DSTM32G4 -c -I../Inc -I"/Users/dhanushd/STM32CubeIDE/workspace_2.0.0/stm32491re_drivers/drivers/Inc" -I"/Users/dhanushd/STM32CubeIDE/workspace_2.0.0/stm32491re_drivers/drivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/002LED_Toggle.cyclo ./Src/002LED_Toggle.d ./Src/002LED_Toggle.o ./Src/002LED_Toggle.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

