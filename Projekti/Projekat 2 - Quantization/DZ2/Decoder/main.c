//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Audio Decoder
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "Dsplib.h"
#include <string.h>

#include "decode.h"
#include "WAVheader.h"
#include "quant.h"


static DSP_HEADER inputHeader;
static WAV_HEADER outputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(CompressedBuffer,4)
Int16 CompressedBuffer[FRAME_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];



/*
 *
 *  main( )
 *
 */
void main( void )
{
	/* Initialize BSL */
    EZDSP5535_init( );

    printf("\n OAiS DSP 1 - Audio Decoder \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    aic3204_set_input_filename("Naziv ulazne datoteke");
	aic3204_set_output_filename("Naziv izlazne datoteke");
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();

    aic3204_read_dsp1_header(&inputHeader);

    memcpy(&outputWAVhdr, &defaultWavHeader, sizeof(outputWAVhdr));

    outputWAVhdr.data.SubChunk2Size = inputHeader.size/2;
    outputWAVhdr.riff.ChunkSize = outputWAVhdr.data.SubChunk2Size + outputWAVhdr.HeaderSize;

    // TODO: Procitati relevantne parametre iz zaglavlja inputHeader



    aic3204_write_wav_header(&outputWAVhdr);

    init_vorbis_window(AUDIO_IO_SIZE);

    while(aic3204_read_data(CompressedBuffer, FRAME_SIZE) == FRAME_SIZE)
	{
    	// Petlja cita dvostruki okvir iz datoteke (jedan okvir podataka za levi i jedan za desni kanal)
    	// FRAME_SIZE = 2(kanala) * 2(dvostruka dužina okvira zbog preklopi-saberi) * AUDIO_IO_SIZE = 512
		// TODO: Pozvati funkciju za dekodovanje i zapisati izlaz u izlaznu datoteku.



	}

	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

