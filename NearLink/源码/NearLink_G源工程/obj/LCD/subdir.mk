################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD/flash.c \
../LCD/lcd.c \
../LCD/spi.c 

OBJS += \
./LCD/flash.o \
./LCD/lcd.o \
./LCD/spi.o 

C_DEPS += \
./LCD/flash.d \
./LCD/lcd.d \
./LCD/spi.d 


# Each subdirectory must supply rules for building sources it contributes
LCD/%.o: ../LCD/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\32806\Desktop\星閃\USART—Interrupt\源工程\Debug" -I"C:\Users\32806\Desktop\星閃\USART—Interrupt\源工程\Core" -I"C:\Users\32806\Desktop\星閃\USART—Interrupt\源工程\User" -I"C:\Users\32806\Desktop\星閃\USART—Interrupt\源工程\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

