//////////////////////////////////////////////////////////////////////////////
// *
// * Laboratorijske vezbe iz OAiS DSP 1
// * Godina: 2020
// *
// * Vezba 8: Ekvalizacija audio signala
// * Autor: Ognjen Stojisavljevic RA 155/2019
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

#include "selvingLP_coefs.h"

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
#pragma DATA_ALIGN(sampleBuffer,4)
Int16 sampleBuffer[AUDIO_IO_SIZE];

Int16 histLP_x[2] = {0,0};
Int16 histLP_y[2] = {0,0};

Int16 histRP_x[2] = {0,0};
Int16 histRP_y[2] = {0,0};

Int16 histP_x[2] = {0,0};
Int16 histP_y[2] = {0,0};

void main( void )
{   
	Int32 i, j;
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

    float k = 2.0;
    // fc = 0,05559988778578521051709504983079
    /*sampleBufferL[0] = shelvingLP(16000, selvingLP_coef, histLP_x, histLP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
    	sampleBufferL[j] = shelvingLP(0, selvingLP_coef, histLP_x, histLP_y, k);
    }*/

    /*sampleBufferL[0] = shelvingHP(16000, selvingHP_coef, histLP_x, histLP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
        sampleBufferL[j] = shelvingHP(0, selvingHP_coef, histLP_x, histLP_y, k);
    }*/

    /*sampleBufferL[0] = first_order_IIR(16000, selvingLP_coef, histLP_x, histLP_y);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
        sampleBufferL[j] = first_order_IIR(0, selvingLP_coef, histLP_x, histLP_y);
    }*/

    /*sampleBufferL[0] = shelvingPeek(16000, selvingSecondOrder2_coef, histLP_x, histLP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
        sampleBufferL[j] = shelvingPeek(0, selvingSecondOrder2_coef, histLP_x, histLP_y, k);
    }*/

    sampleBufferL[0] = shelvingLP(16000, selvingLP_coef, histLP_x, histLP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
    	sampleBufferL[j] = shelvingLP(0, selvingLP_coef, histLP_x, histLP_y, k);
    }

    sampleBufferR[0] = shelvingHP(sampleBufferL[0], selvingHP_coef, histRP_x, histRP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
        sampleBufferR[j] = shelvingHP(0, selvingHP_coef, histRP_x, histRP_y, k);
    }

    sampleBuffer[0] = shelvingPeek(sampleBufferR[0], selvingSecondOrder2_coef, histP_x, histP_y, k);
    for(j = 1; j < AUDIO_IO_SIZE; j++)
    {
        sampleBuffer[j] = shelvingPeek(0, selvingSecondOrder2_coef, histP_x, histP_y, k);
    }

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


