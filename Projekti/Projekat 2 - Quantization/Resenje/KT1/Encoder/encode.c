//////////////////////////////////////////////////////////////////////////////
// * File name: encode.c
// *
// *
// * Description: Audio Decoder
// * Course: OAiS DSP1
// * Year: 2021
// *
// * Author: <Ognjen Stojisavljevic RA 155/2019>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////
#include "encode.h"

#include "Dsplib.h"
#include "ezdsp5535_aic3204_dma.h"
#include <math.h>
#include "quant.h"


#define PI 3.1415926535
#define FFT_SIZE (2*AUDIO_IO_SIZE)

#pragma DATA_ALIGN(fft_buffer,4)
static Int16 fft_bufferL[FFT_SIZE];
static Int16 fft_bufferR[FFT_SIZE];

static Int16 in_delayL[FFT_SIZE/2];
static Int16 in_delayR[FFT_SIZE/2];

Int16 window[FFT_SIZE];


void init_vorbis_window(Int16 N)
{
  int i;
  double t;

  for (i = 0; i < N; i++) {
    t = sin(0.5 * PI * (i + 0.5) / N);
    window[i] = 32767 * sin(0.5 * PI * t * t);
    window[2*N-1-i] = window[i];
  }
}


Int16 znak[FFT_SIZE];

// TODO: Realizovati funkciju za enkodovanje i unutar nje uraditi analizu i kvantizaciju za svaki kanal ponaosob
void encode(Int16* inL, Int16* inR, Int16* out, Int16 N, Uint16 BL, Uint16 BR)
{
	int i = 0;

	// FFT LEVOG KANALA
	for(i = 0; i < N; i++)
	{
		fft_bufferL[i] = in_delayL[i];
		fft_bufferL[i + N] = inL[i];
		in_delayL[i] = inL[i];
	}
	// SLIKATI

	for(i = 0; i < 2*N; i++)
	{
		fft_bufferL[i] = _smpy(fft_bufferL[i], window[i]);
	}
	// SLIKATI

	rfft(fft_bufferL, FFT_SIZE, SCALE);							// FFT
	// SLIKATI

	// FFT DESNOG KANALA
	for(i = 0; i < N; i++)
	{
		fft_bufferR[i] = in_delayR[i];
		fft_bufferR[i + N] = inR[i];
		in_delayR[i] = inR[i];
	}

	for(i = 0; i < 2*N; i++)
	{
		fft_bufferR[i] = _smpy(fft_bufferR[i], window[i]);
	}

	rfft(fft_bufferR, FFT_SIZE, SCALE);							// FFT


	// KVANTIZACIJA
	for(i = 0; i < 2*N; i++) // LEVI
	{
		fft_bufferL[i] = quantB(fft_bufferL[i], BL);
	}
	// SLIKATI

	for(i = 0; i < 2*N; i++) // DESNI
	{
		fft_bufferR[i] = quantB(fft_bufferR[i], BR);
	}

	// SPAJANJE LEVOG I DESNOG KANALA
	for(i = 0; i < 2*N; i++)
	{
		out[2*i] = fft_bufferL[i];
		out[2*i + 1] = fft_bufferR[i];
	}
}


