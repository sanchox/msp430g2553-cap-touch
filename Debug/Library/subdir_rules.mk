################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Library/CTS_HAL.obj: ../Library/CTS_HAL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/sanchox/ti/ccsv7/tools/compiler/ti-cgt-msp430_18.1.0.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="/home/sanchox/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/sanchox/ti/workspace_v7/MyTouch" --include_path="/home/sanchox/ti/workspace_v7/MyTouch/Library" --include_path="/home/sanchox/ti/ccsv7/tools/compiler/ti-cgt-msp430_18.1.0.LTS/include" --advice:power="all" --define=__MSP430G2553__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Library/CTS_HAL.d_raw" --obj_directory="Library" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Library/CTS_Layer.obj: ../Library/CTS_Layer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/sanchox/ti/ccsv7/tools/compiler/ti-cgt-msp430_18.1.0.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="/home/sanchox/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/sanchox/ti/workspace_v7/MyTouch" --include_path="/home/sanchox/ti/workspace_v7/MyTouch/Library" --include_path="/home/sanchox/ti/ccsv7/tools/compiler/ti-cgt-msp430_18.1.0.LTS/include" --advice:power="all" --define=__MSP430G2553__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Library/CTS_Layer.d_raw" --obj_directory="Library" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


