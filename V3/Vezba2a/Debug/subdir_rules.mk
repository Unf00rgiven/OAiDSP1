################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
gen_sinus.obj: ../gen_sinus.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti2/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/ti2/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/Ognjen/Desktop/Fax/III godina/I semestar/Osnovi algoritama i DSP/Vezbe/Racunarske/V2/Vezba2a/c55xx_csl/inc" --include_path="C:/Users/Ognjen/Desktop/Fax/III godina/I semestar/Osnovi algoritama i DSP/Vezbe/Racunarske/V2/Vezba2a/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="gen_sinus.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti2/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/ti2/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/Ognjen/Desktop/Fax/III godina/I semestar/Osnovi algoritama i DSP/Vezbe/Racunarske/V2/Vezba2a/c55xx_csl/inc" --include_path="C:/Users/Ognjen/Desktop/Fax/III godina/I semestar/Osnovi algoritama i DSP/Vezbe/Racunarske/V2/Vezba2a/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


