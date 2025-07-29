################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1425208417: ../MaixCam_Com.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ti/CCS2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "E:/CCS/MaixCam_Com/MaixCam_Com.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_05_01_00/.metadata/product.json" -d "MSPM0G350X" -p "VQFN-48(RGZ)" -r "Default" --context "system" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1425208417 ../MaixCam_Com.syscfg
device.opt: build-1425208417
device.cmd.genlibs: build-1425208417
ti_msp_dl_config.c: build-1425208417
ti_msp_dl_config.h: build-1425208417
Event.dot: build-1425208417

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/CCS2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/CCS/MaixCam_Com/BSP" -I"E:/CCS/MaixCam_Com" -I"E:/CCS/MaixCam_Com/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/CCS2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/CCS/MaixCam_Com/BSP" -I"E:/CCS/MaixCam_Com" -I"E:/CCS/MaixCam_Com/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/CCS2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"E:/CCS/MaixCam_Com/BSP" -I"E:/CCS/MaixCam_Com" -I"E:/CCS/MaixCam_Com/Debug" -I"C:/ti/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


