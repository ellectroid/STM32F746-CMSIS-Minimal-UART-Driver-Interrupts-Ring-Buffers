################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/main.c \
../Src/rcc.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart1.c 

OBJS += \
./Src/gpio.o \
./Src/main.o \
./Src/rcc.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart1.o 

C_DEPS += \
./Src/gpio.d \
./Src/main.d \
./Src/rcc.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart1.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F746NGHx -DSTM32F7 -c -I../Inc -I"C:/Users/User/Desktop/STM32F746/chip_headers/Include" -I"C:/Users/User/Desktop/STM32F746/chip_headers/Device/ST/STM32F7xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

