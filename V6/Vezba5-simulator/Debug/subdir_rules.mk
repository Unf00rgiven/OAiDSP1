################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
WAVheader.obj: ../WAVheader.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="WAVheader.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204.obj: ../aic3204.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_init.obj: ../aic3204_init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204_init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

direct_form_iir.obj: ../direct_form_iir.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="direct_form_iir.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ezdsp5535_aic3204_dma.obj: ../ezdsp5535_aic3204_dma.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="ezdsp5535_aic3204_dma.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

iir.obj: ../iir.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="iir.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O0 -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/c55xx_csl/inc" --include_path="C:/Users/dbokan/workspace_oaisdsp120201/Vezba5-simulator/include" --define=c5535 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


