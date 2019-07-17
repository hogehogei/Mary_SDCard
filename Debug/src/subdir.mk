################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Mary_SDCard.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc11xx.cpp \
../src/initialize.cpp \
../src/interrupt.cpp 

C_SRCS += \
../src/crp.c 

OBJS += \
./src/Mary_SDCard.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/initialize.o \
./src/interrupt.o 

CPP_DEPS += \
./src/Mary_SDCard.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc11xx.d \
./src/initialize.d \
./src/interrupt.d 

C_DEPS += \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -DCPP_NO_HEAP -D__LPC11XX__ -I"C:\Users\hogehogei\Desktop\Mary_SDCard\Mary_SDCard\inc" -Og -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -std=c++11 -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -DCPP_NO_HEAP -D__LPC11XX__ -D__NEWLIB__ -I"C:\Users\hogehogei\Desktop\Mary_SDCard\Mary_SDCard\inc" -Og -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


