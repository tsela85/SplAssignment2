################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AppLogger.cpp \
../src/Company.cpp \
../src/CompanyTest.cpp \
../src/EventsConfiguration.cpp \
../src/HRCReport.cpp \
../src/JobType.cpp \
../src/main.cpp 

OBJS += \
./src/AppLogger.o \
./src/Company.o \
./src/CompanyTest.o \
./src/EventsConfiguration.o \
./src/HRCReport.o \
./src/JobType.o \
./src/main.o 

CPP_DEPS += \
./src/AppLogger.d \
./src/Company.d \
./src/CompanyTest.d \
./src/EventsConfiguration.d \
./src/HRCReport.d \
./src/JobType.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/Poco -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


