################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
BSP/%.o: ../BSP/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/CCS2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/CCS/24_H" -I"E:/CCS/24_H/BSP" -I"E:/CCS/24_H/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -I"C:/ti/mspm0_sdk_2_05_01_00/source/ti/driverlib" -gdwarf-3 -MMD -MP -MF"BSP/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


