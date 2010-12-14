################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AppLogger.cpp \
../src/Command.cpp \
../src/Company.cpp \
../src/CompanyTest.cpp \
../src/HRC.cpp \
../src/HRCReport.cpp \
../src/Job.cpp \
../src/JobType.cpp \
../src/ReadFile.cpp \
../src/SkillType.cpp \
../src/Worker.cpp \
../src/main.cpp 

OBJS += \
./src/AppLogger.o \
./src/Command.o \
./src/Company.o \
./src/CompanyTest.o \
./src/HRC.o \
./src/HRCReport.o \
./src/Job.o \
./src/JobType.o \
./src/ReadFile.o \
./src/SkillType.o \
./src/Worker.o \
./src/main.o 

CPP_DEPS += \
./src/AppLogger.d \
./src/Command.d \
./src/Company.d \
./src/CompanyTest.d \
./src/HRC.d \
./src/HRCReport.d \
./src/Job.d \
./src/JobType.d \
./src/ReadFile.d \
./src/SkillType.d \
./src/Worker.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/Poco -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


