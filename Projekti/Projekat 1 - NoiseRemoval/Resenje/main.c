//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Course assignment 1 - Noise removal
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"
#include "fir.h"
#include "iir.h"
#include "coeff.h"

#define CHANNEL_NUM 2

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#pragma DATA_ALIGN(outputBufferL, 4)
Int16 inputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferR, 4)
Int16 inputBufferR[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferL, 4)
Int16 outputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferR, 4)
Int16 outputBufferR[AUDIO_IO_SIZE];

#define SAMPLE_RATE 48000L
#define GAIN_IN_dB 0

Int16 dirac[AUDIO_IO_SIZE];
Int16 diracResponse[AUDIO_IO_SIZE];

//TO DO: Create history buffer here
Int16 dirac[AUDIO_IO_SIZE];
Int16 diracResponse[AUDIO_IO_SIZE];


Int16 history_low33[F1_COEFFS];
Int16 history_low33_sigL[F1_COEFFS];
Int16 history_low33_sigR[F1_COEFFS];
Uint16 p_state_low33;
Uint16 p_state_low33_sigL;
Uint16 p_state_low33_sigR;


Int16 history_low121[F2_COEFFS];
Int16 history_low121_sigL[F2_COEFFS];
Int16 history_low121_sigR[F2_COEFFS];
Uint16 p_state_low121;
Uint16 p_state_low121_sigL;
Uint16 p_state_low121_sigR;


Int16 history_x[2];
Int16 history_y[2];
Int16 history_xsigL[2];
Int16 history_ysigL[2];
Int16 history_xsigR[2];
Int16 history_ysigR[2];

Int16 history_1[3][2];
Int16 history_2[3][2];
Int16 history_1sigL[3][2];
Int16 history_1sigR[3][2];
Int16 history_2sigL[3][2];
Int16 history_2sigR[3][2];




/*
 *
 *  main( )
 *
 */
void main( void )
{
	Int32 i, j;
	Int32 number_of_blocks;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initializatition
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize BSL
    EZDSP5535_init( );

    printf("\n OAiS DSP 1 - Second assignment 2018. \n");

    // Initialise hardware interface and I2C for code
    aic3204_hardware_init();

    aic3204_set_input_filename("../signal1.wav");
	aic3204_set_output_filename("../out_signal1.wav");

    // Initialise the AIC3204 codec
	aic3204_init();

    // Setup sampling frequency and 30dB gain for microphone
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN_IN_dB);

    aic3204_read_wav_header(&inputWAVhdr);

	// Set up output WAV header
	outputWAVhdr = inputWAVhdr;

	number_of_blocks = inputWAVhdr.data.SubChunk2Size/
			(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

	aic3204_write_wav_header(&outputWAVhdr);

	dirac[0] = 32767;
	    for(i=1;i<AUDIO_IO_SIZE;i++)
	    {
	    	dirac[i] = 0;
	    }

	// Processing loop. Place your code here...
    for(i = 0; i < number_of_blocks; i++)
    {
    	aic3204_read_block(inputBufferL, inputBufferR);

    	for(j = 0; j < AUDIO_IO_SIZE; j++)
    	{
			// ZADATAK 2
    		//diracResponse[j] = fir_circular(dirac[j], filter1_coeffs, history_low33, F1_COEFFS, &p_state_low33);
    		//outputBufferL[j] = fir_circular(inputBufferL[j], filter1_coeffs, history_low33_sigL, F1_COEFFS, &p_state_low33_sigL);
    		//outputBufferR[j] = fir_circular(inputBufferR[j], filter1_coeffs, history_low33_sigR, F1_COEFFS, &p_state_low33_sigR);

    		// ZADATAK 3
    		diracResponse[j] = fir_circular(dirac[j], filter2_coeffs, history_low121, F2_COEFFS, &p_state_low121);
    		outputBufferL[j] = fir_circular(inputBufferL[j], filter2_coeffs, history_low121_sigL, F2_COEFFS, &p_state_low121_sigL);
    		outputBufferR[j] = fir_circular(inputBufferR[j], filter2_coeffs, history_low121_sigR, F2_COEFFS, &p_state_low121_sigR);

    		// ZADATAK 5
    		//diracResponse[j] = second_order_IIR(dirac[j], iir_notch_coeffs, history_x, history_y);
    		//outputBufferL[j] = second_order_IIR(inputBufferL[j], iir_notch_coeffs, history_xsigL, history_ysigL);
       		//outputBufferR[j] = second_order_IIR(inputBufferR[j], iir_notch_coeffs, history_xsigR, history_ysigR);

    		//ZADATAK 6
    		//diracResponse[j] = sixth_order_IIR(dirac[j], iir_notch_coeffsmatrix, history_1, history_2);
    		//outputBufferL[j] = sixth_order_IIR(inputBufferL[j], iir_notch_coeffsmatrix, history_1sigL, history_2sigL);
    		//outputBufferR[j] = sixth_order_IIR(inputBufferR[j], iir_notch_coeffsmatrix, history_1sigR, history_2sigR);

    	}
    	aic3204_write_block(outputBufferL, outputBufferR);
	}


	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

