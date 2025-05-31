################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DMA_Prog.c \
../Src/GPIO_prog.c \
../Src/NVIC_prog.c \
../Src/RCC_Driver.c \
../Src/SysTick_prog.c \
../Src/USART_Prog.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/DMA_Prog.o \
./Src/GPIO_prog.o \
./Src/NVIC_prog.o \
./Src/RCC_Driver.o \
./Src/SysTick_prog.o \
./Src/USART_Prog.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/DMA_Prog.d \
./Src/GPIO_prog.d \
./Src/NVIC_prog.d \
./Src/RCC_Driver.d \
./Src/SysTick_prog.d \
./Src/USART_Prog.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/DMA_Prog.cyclo ./Src/DMA_Prog.d ./Src/DMA_Prog.o ./Src/DMA_Prog.su ./Src/GPIO_prog.cyclo ./Src/GPIO_prog.d ./Src/GPIO_prog.o ./Src/GPIO_prog.su ./Src/NVIC_prog.cyclo ./Src/NVIC_prog.d ./Src/NVIC_prog.o ./Src/NVIC_prog.su ./Src/RCC_Driver.cyclo ./Src/RCC_Driver.d ./Src/RCC_Driver.o ./Src/RCC_Driver.su ./Src/SysTick_prog.cyclo ./Src/SysTick_prog.d ./Src/SysTick_prog.o ./Src/SysTick_prog.su ./Src/USART_Prog.cyclo ./Src/USART_Prog.d ./Src/USART_Prog.o ./Src/USART_Prog.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

