//////////////////////////////////////////////////////////////////////////////
// * File name: decode.c
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

#include "decode.h"

#include "Dsplib.h"
#include "ezdsp5535_aic3204_dma.h"
#include <math.h>
#include "quant.h"


#define PI 3.1415926535
#define FFT_SIZE (2*AUDIO_IO_SIZE)

//Niz koji ce biti prosledjen funkciji rifft mora biti poravnat na 4.
#pragma DATA_ALIGN(fft_buffer,4)
 Int16 fft_bufferL[FFT_SIZE*2];
 Int16 fft_bufferR[FFT_SIZE*2];

 static Int16 out_delayL[FFT_SIZE/2];
 static Int16 out_delayR[FFT_SIZE/2];

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

// TODO: Realizovati funkciju za dekodovanje i unutar nje uraditi vracanje u opseg i sintezu za svaki kanal ponaosob.
void decode(Int16* in, Int16* outL, Int16* outR, Int16 N, Uint16 BL, Uint16 BR)
{
	int i = 0;

	// LEVI KANAL
	for(i = 0; i < 2*N; i++)
	{
		fft_bufferL[i] = in[2*i];										// UCITAVAMO OKVIR ZA LEVI KANAL
	}

	for(i = 0; i < 2*N; i++)
	{
		fft_bufferL[i] = reconstructB(fft_bufferL[i], BL);				// REKONSTRUKCIJA
	}

	rifft(fft_bufferL, FFT_SIZE, NOSCALE);								// INVERZNA FFT
	// SLIKATI

	for(i = 0; i < N; i++)
	{
		outL[i] = _smpy(fft_bufferL[i], window[i]) + _smpy(out_delayL[i], window[i + N]);
		outL[i] = outL[i] * 4;
		out_delayL[i] = fft_bufferL[i + N];								// DELAY CUVA DRUGIH N OBRIRAKA ZA NAREDNU ITERACIJU
	}

	// DESNI KANAL
	for(i = 0; i < 2*N; i++)
	{
		fft_bufferR[i] = in[2*i + 1];									//UCITAVAMO OKVIR ZA DESNI KANAL
	}

	for(i = 0; i < 2*N; i++)
	{
		fft_bufferR[i] = reconstructB(fft_bufferR[i], BR);				// REKONSTRUKCIJA
	}

	rifft(fft_bufferR, FFT_SIZE, NOSCALE);								// INVERZNA FFT

	for(i = 0; i < N; i++)
	{
		outR[i] = _smpy(fft_bufferR[i], window[i]) + _smpy(out_delayR[i], window[i + N]);
		outR[i] = outR[i] * 4;
		out_delayR[i] = fft_bufferR[i + N];							// DELAY CUVA DRUGIH N OBRIRAKA ZA NAREDNU ITERACIJU
	}

}

