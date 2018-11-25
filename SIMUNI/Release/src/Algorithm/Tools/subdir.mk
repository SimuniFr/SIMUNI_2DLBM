################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm/Tools/ContactAngle.cpp \
../src/Algorithm/Tools/Extrapolation.cpp \
../src/Algorithm/Tools/ExtrapolationDEF.cpp \
../src/Algorithm/Tools/Gradients.cpp \
../src/Algorithm/Tools/GradientsDEF.cpp \
../src/Algorithm/Tools/Interpolation.cpp \
../src/Algorithm/Tools/InterpolationDEF.cpp 

OBJS += \
./src/Algorithm/Tools/ContactAngle.o \
./src/Algorithm/Tools/Extrapolation.o \
./src/Algorithm/Tools/ExtrapolationDEF.o \
./src/Algorithm/Tools/Gradients.o \
./src/Algorithm/Tools/GradientsDEF.o \
./src/Algorithm/Tools/Interpolation.o \
./src/Algorithm/Tools/InterpolationDEF.o 

CPP_DEPS += \
./src/Algorithm/Tools/ContactAngle.d \
./src/Algorithm/Tools/Extrapolation.d \
./src/Algorithm/Tools/ExtrapolationDEF.d \
./src/Algorithm/Tools/Gradients.d \
./src/Algorithm/Tools/GradientsDEF.d \
./src/Algorithm/Tools/Interpolation.d \
./src/Algorithm/Tools/InterpolationDEF.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm/Tools/%.o: ../src/Algorithm/Tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -O3 -Wall -c -fmessage-length=0 -lcgns -lhdf5 -lboost_serialization -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


