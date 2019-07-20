################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc_tread_entry.c \
../src/guiapp_event_handlers.c \
../src/hal_entry.c \
../src/mainTick.c \
../src/main_thread_entry.c \
../src/pwm_thread_entry.c 

OBJS += \
./src/adc_tread_entry.o \
./src/guiapp_event_handlers.o \
./src/hal_entry.o \
./src/mainTick.o \
./src/main_thread_entry.o \
./src/pwm_thread_entry.o 

C_DEPS += \
./src/adc_tread_entry.d \
./src/guiapp_event_handlers.d \
./src/hal_entry.d \
./src/mainTick.d \
./src/main_thread_entry.d \
./src/pwm_thread_entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	C:\Renesas\Synergy\e2studio_v7.3.0_ssp_v1.6.3\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy_cfg\ssp_cfg\driver" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\bsp" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\driver\api" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\driver\instances" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\src" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\src\synergy_gen" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy_cfg\ssp_cfg\framework" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\framework\api" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\framework\instances" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\framework\tes" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\inc\framework\el" -I"C:\Users\Tonat\e2_studio\workspace\Integrador\synergy\ssp\src\framework\el\tx" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


