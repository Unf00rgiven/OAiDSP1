//////////////////////////////////////////////////////////////////////////////
// *
// * Laboratorijske vezbe iz OAiS DSP 1
// * Godina: 2020
// *
// * Vezba 8: Ekvalizacija audio signala
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
#include "math.h"

#include "iir.h"
#include "processing.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 16000L

#define PI 3.14159265

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

/* Niz za smestanje ulaznih i izlaznih odbiraka */
#pragma DATA_ALIGN(sampleBufferL,4)
Int16 sampleBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(sampleBufferR,4)
Int16 sampleBufferR[AUDIO_IO_SIZE];



void main( void )
{   
	Int32 i;
	Int32 number_of_blocks;
	
    /* Inicijalizaija razvojne ploce */
    EZDSP5535_init( );

	/* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();

    aic3204_set_input_filename("../signal1.wav");
    aic3204_set_output_filename("../out_signal1.wav");

    /* Inicijalizacija AIC3204 kodeka */
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

    for(i = 0; i < number_of_blocks; i++)
    {
    	aic3204_read_block(sampleBufferL, sampleBufferR);

    	/* Your code here */

		aic3204_write_block(sampleBufferL, sampleBufferR);
	}


	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}


