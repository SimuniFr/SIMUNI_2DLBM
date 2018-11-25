################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm/LowOrder/Boundaries/D2Q9Bc.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9BcVar.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Corner.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9GenericBc.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9GlobalCorner.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Periodic.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Pressure.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9SpecialWall.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Symmetry.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Velocity.cpp \
../src/Algorithm/LowOrder/Boundaries/D2Q9Wall.cpp 

OBJS += \
./src/Algorithm/LowOrder/Boundaries/D2Q9Bc.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9BcVar.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Corner.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9GenericBc.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9GlobalCorner.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Periodic.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Pressure.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9SpecialWall.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Symmetry.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Velocity.o \
./src/Algorithm/LowOrder/Boundaries/D2Q9Wall.o 

CPP_DEPS += \
./src/Algorithm/LowOrder/Boundaries/D2Q9Bc.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9BcVar.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Corner.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9GenericBc.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9GlobalCorner.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Periodic.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Pressure.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9SpecialWall.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Symmetry.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Velocity.d \
./src/Algorithm/LowOrder/Boundaries/D2Q9Wall.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm/LowOrder/Boundaries/%.o: ../src/Algorithm/LowOrder/Boundaries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -O3 -Wall -c -fmessage-length=0 -lcgns -lhdf5 -lboost_serialization -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


