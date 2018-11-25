################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Mesh/SingleBlock/Patch/PatchBc.cpp \
../src/Mesh/SingleBlock/Patch/PatchBcDEF.cpp 

OBJS += \
./src/Mesh/SingleBlock/Patch/PatchBc.o \
./src/Mesh/SingleBlock/Patch/PatchBcDEF.o 

CPP_DEPS += \
./src/Mesh/SingleBlock/Patch/PatchBc.d \
./src/Mesh/SingleBlock/Patch/PatchBcDEF.d 


# Each subdirectory must supply rules for building sources it contributes
src/Mesh/SingleBlock/Patch/%.o: ../src/Mesh/SingleBlock/Patch/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -O0 -g3 -Wall -c -fmessage-length=0 -lcgns -lhdf5 -lboost_serialization -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


