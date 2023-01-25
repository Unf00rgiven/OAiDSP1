//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 4
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"
#include "fir.h"

#include "low_pass_8th_order.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/* TO DO: Define history buffers and Rd/Wr pointers*/
/* Your code here */
Int16 dirac[AUDIO_IO_SIZE];
Int16 diracResponse[AUDIO_IO_SIZE];

Int16 history_low8[LP_LENGTH];
Int16 history_low8_sigL[LP_LENGTH];
Int16 history_low8_sigR[LP_LENGTH];

Uint16 p_state_low8;
Uint16 p_state_low8_sigL;
Uint16 p_state_low8_sigR;

Int16 history_low32[LP_LENGTH];
Int16 history_low32_sigL[LP_LENGTH];
Int16 history_low32_sigR[LP_LENGTH];

Uint16 p_state_low32;
Uint16 p_state_low32_sigL;
Uint16 p_state_low32_sigR;

Int16 history_low120[LP_LENGTH];
Int16 history_low120_sigL[LP_LENGTH];
Int16 history_low120_sigR[LP_LENGTH];

Uint16 p_state_low120;
Uint16 p_state_low120_sigL;
Uint16 p_state_low120_sigR;
/*
 *
 *  main( )
 *
 */
void main( void )
{   
	int i, j;
	Int32 number_of_blocks;

	/* Initialize BSL */
    EZDSP5535_init( );

	printf("\n OAiS DSP 1 - Vezba 4 \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
	aic3204_set_input_filename("../../streams/signal1.wav");
	aic3204_set_output_filename("../out_signal1.wav");
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
	
	aic3204_read_wav_header(&inputWAVhdr);

    // Set up output WAV header
    outputWAVhdr = inputWAVhdr;

    number_of_blocks = inputWAVhdr.data.SubChunk2Size/
    			(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

    aic3204_write_wav_header(&outputWAVhdr);

    /* TO DO: Initialize history buffers to 0 */
    /* Your code here */

    dirac[0] = 32767;
    for(i=1;i<AUDIO_IO_SIZE;i++)
    {
    	dirac[i] = 0;
    }

	for(i=0;i<number_of_blocks;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* TO DO: Invoke filtering routine */
		/* Your code here */

		for(j = 0; j < AUDIO_IO_SIZE; j++)
		{
			diracResponse[j] = fir_circular(dirac[j], lowpass_5kHz_8th_order, history_low8, LP_LENGTH, &p_state_low8);
			OutputBufferL[j] = fir_circular(InputBufferL[j], lowpass_5kHz_8th_order, history_low8_sigL, LP_LENGTH, &p_state_low8_sigL);
			OutputBufferR[j] = fir_circular(InputBufferR[j], lowpass_5kHz_8th_order, history_low8_sigR, LP_LENGTH, &p_state_low8_sigR);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
