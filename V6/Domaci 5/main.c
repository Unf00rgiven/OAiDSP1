//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 5
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: Ognjen Stojisavljevic RA155/2019
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"
#include "iir.h"
#include "IIR_low_pass_filters.h"
#include "IIR_high_pass_filters.h"
#include "IIR_band_pass_filters.h"
#include "IIR_all_pass_filters.h"

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

Int16 x_history[2];
Int16 y_history[2];

//Int16 x_history[2][2];
//Int16 y_history[2][2];

//Int16 x_history_sigL[2];
//Int16 y_history_sigL[2];

//Int16 x_history_sigR[2];
//Int16 y_history_sigR[2];

Int16 x_history_sigL[2][2];
Int16 y_history_sigL[2][2];

Int16 x_history_sigR[2][2];
Int16 y_history_sigR[2][2];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	int i;
	Int32 j;
	Int32 number_of_blocks;

	/* Initialize BSL */
    EZDSP5535_init( );

	printf("\n OAiS DSP 1 - Vezba 5 \n");

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
			//diracResponse[j] = second_order_IIR(dirac[j], IIR_low_pass_5000Hz_2nd_order, x_history, y_history);
			//diracResponse[j] = fourth_order_IIR(dirac[j], IIR_low_pass_5000Hz_4th_order, x_history, y_history);
			//diracResponse[j] = fourth_order_IIR(dirac[j], IIR_high_pass_12000Hz_4th_order, x_history, y_history);
			//diracResponse[j] = fourth_order_IIR(dirac[j], IIR_band_pass_5kHz_12kHz_4th_order, x_history, y_history);
			diracResponse[j] = second_order_IIR(dirac[j], IIR_all_pass_2nd_order, x_history, y_history);

			//OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_2nd_order, x_history_sigL, y_history_sigL);
			//OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_all_pass_2nd_order, x_history_sigL, y_history_sigL);
			OutputBufferL[j] = Nth_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_4th_order, x_history_sigL, y_history_sigL, 4);
			//OutputBufferR[j] = fourth_order_IIR(InputBufferR[j], IIR_low_pass_5000Hz_4th_order, x_history_sigR, y_history_sigR);
			//OutputBufferR[j] = fourth_order_IIR(InputBufferR[j], IIR_high_pass_12000Hz_4th_order, x_history_sigR, y_history_sigR);
			//OutputBufferR[j] = fourth_order_IIR(InputBufferR[j], IIR_band_pass_5kHz_12kHz_4th_order, x_history_sigR, y_history_sigR);
			OutputBufferR[j] = Nth_order_IIR(InputBufferR[j], IIR_low_pass_5000Hz_6th_order, x_history_sigR, y_history_sigR, 6);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

