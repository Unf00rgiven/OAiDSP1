//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 2
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - Ognjen Stojisavljevic RA 155/2019>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"
#include "quant.h"

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

    printf("\n OAiS DSP 1 - Vezba 2 \n");

    // Initialise hardware interface and I2C for code
    aic3204_hardware_init();

    //aic3204_set_input_filename("../acoustic_guitar.wav");
    aic3204_set_input_filename("../signal1.wav");
	aic3204_set_output_filename("../out_signal1.wav");

    // Initialise the AIC3204 codec
	aic3204_init();

    aic3204_read_wav_header(&inputWAVhdr);

	// Set up output WAV header
	outputWAVhdr = inputWAVhdr;

	number_of_blocks = inputWAVhdr.data.SubChunk2Size/
			(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

	aic3204_write_wav_header(&outputWAVhdr);

	// Processing loop. Place your code here...
    for(i = 0; i < number_of_blocks; i++)
    {
    	aic3204_read_block(inputBufferL, inputBufferR);

    	for(j = 0; j < AUDIO_IO_SIZE; j++)
    	{
    		//outputBufferL[j] = wrapAroundB(inputBufferL[j], 15) << 1;
    		//outputBufferR[j] = clipB(inputBufferR[j], 15) << 1;

    		//outputBufferL[j] = wrapAroundB(inputBufferL[j], 13) << 3;
       		//outputBufferR[j] = clipB(inputBufferR[j], 13) << 3;

    		// Zadatak 7
    		outputBufferL[j] = clipB(inputBufferL[j], 10) << 6;
    		outputBufferR[j] = clipB(inputBufferR[j], 10) << 6;
    	}

    	aic3204_write_block(outputBufferL, outputBufferR);
	}


	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

