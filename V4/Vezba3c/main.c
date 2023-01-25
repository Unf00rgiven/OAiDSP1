//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 3
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "math.h"
#include "sine.h"
#include "WAVheader.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define PI 3.141592653589793238

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

Int16 zeros[AUDIO_IO_SIZE];

Int32 DFTReal[AUDIO_IO_SIZE];
Int32 DFTImag[AUDIO_IO_SIZE];

Int32 magnitude[AUDIO_IO_SIZE/2];
/*
 *
 *  main( )
 *
 */

void dft(float inreal[], float inimag[], float outreal[], float outimag[], Int16 N)
{
	int n, k;
    for ( n = 0; n < N; n++) {
        float sumreal = 0;
        float sumimag = 0;
        for (k = 0; k < N; k++) {
            sumreal +=  inreal[k] * cos(2 * PI * n * k / N) + inimag[k] * sin(2 * PI * n * k / N);
            sumimag += -inreal[k] *  sin(2 * PI * n * k / N) + inimag[k] * cos(2 * PI * n * k / N);
        }
        outreal[n] = sumreal;
        outimag[n] = sumimag;
    }
}

// TO DO: finish DFT function
void dft_int(Int16 inreal[], Int16 inimag[], Int32 outreal[], Int32 outimag[], Uint16 N)
{
	Uint16 n, k;

	// calculate scale_factor
	/* Your code here */

	for ( n = 0; n < N; n++)
	{
		Int32 sumreal = 0;
	    Int32 sumimag = 0;

	    for (k = 0; k < N; k++)
	    {
	    	// calculate DFT inner loop
	    	/* Your code here */
	    }

	    // store calculated values into output buffers
	    /* Your code here */
	}
}

void main( void )
{   
	Int32 i;
	Int32 number_of_blocks;

	/* Initialize BSL */
    EZDSP5535_init( );

    printf("\n OAiS DSP 1 - Vezba 3c \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    aic3204_set_input_filename("../../streams/sine_1kHz.wav");
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




    for(i = 0; i < AUDIO_IO_SIZE; i++)
    {
    	zeros[i] = 0;
    }

	for(i = 0; i < number_of_blocks; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/*  Your code here */

	}
    	





	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

