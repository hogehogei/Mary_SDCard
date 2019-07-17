################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/drv/sdcard/SDC_Drv_SPI.cpp \
../src/drv/sdcard/SD_Card.cpp 

OBJS += \
./src/drv/sdcard/SDC_Drv_SPI.o \
./src/drv/sdcard/SD_Card.o 

CPP_DEPS += \
./src/drv/sdcard/SDC_Drv_SPI.d \
./src/drv/sdcard/SD_Card.d 


# Each subdirectory must supply rules for building sources it contributes
src/drv/sdcard/%.o: ../src/drv/sdcard/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -DCPP_NO_HEAP -D__LPC11XX__ -I"C:\Users\hogehogei\Desktop\Mary_SDCard\Mary_SDCard\inc" -Og -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -std=c++11 -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


