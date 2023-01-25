//////////////////////////////////////////////////////////////////////////////
// *
// * Laboratorijske vezbe iz OAiS DSP 1
// * Godina: 2020
// *
// * Vezba 9: Adaptivni sistemi
// * Autor:
// *                                                                          
// *                                                                          
/////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "adaptive_filter.h"
//#include "low_pass_8th_order.h"
#include "low_pass_32th_order.h"
#include "fir.h"
#include "stdint.h"

#define SAMPLE_RATE 16000L

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

Int16 adaptive_coeff[FILTER_ORDER] = {0};
Int16 history[FILTER_ORDER] ={0};
Uint16 state = 0;

Int16 history1[LP_ORDER] ={0};
Uint16 state1 = 0;

/*
 *
 *  main( )
 *
 */
void main( void )
{   
	Int16 i, j;
	Int16 number_of_blocks;

    /* Initialize BSL */
    EZDSP5535_init( );

	printf("\n Vezba 9 - Adaptivni sistemi \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    aic3204_set_input_filename("../WhiteNoise.wav");
    aic3204_set_output_filename("../out_signal1.wav");
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
    /* Citanje zaglavlja ulazne datoteke */
    aic3204_read_wav_header(&inputWAVhdr);

    /* Popunjavanje zaglavlja izlazne datoteke */
    outputWAVhdr = inputWAVhdr;

    number_of_blocks = inputWAVhdr.data.SubChunk2Size/
       (inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

    /* Zapis zaglavlja izlazne datoteke */
    aic3204_write_wav_header(&outputWAVhdr);

    /* Initialize filter coeff */
	for(i=0; i < FILTER_ORDER; i++)
	{
		history[i] = 0;
		adaptive_coeff[i] = 0;
	}

	for(i = 0; i < number_of_blocks; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			//Int16 sig = fir_circular(InputBufferL[j], lowpass_5kHz_32th_order, history1, LP_ORDER, &state1);
			Int16 sig = fourth_order_IIR(InputBufferL[j], lowpass_5kHz_32th_order, history1, LP_ORDER, &state1);
			OutputBufferL[j] = lms_filter(InputBufferL[j], sig, adaptive_coeff, history, FILTER_ORDER, &state, 6553);


			//OutputBufferL[j] = lms_filter(InputBufferR[j], InputBufferL[j], adaptive_coeff, history, FILTER_ORDER, &state, 6553);
			OutputBufferR[j] = InputBufferL[j] - InputBufferR[j];
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

