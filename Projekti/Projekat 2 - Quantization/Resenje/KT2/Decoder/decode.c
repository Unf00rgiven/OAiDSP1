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
#pragma DATA_ALIGN(fft_bufferL,4)
#pragma DATA_ALIGN(fft_bufferR,4)
 Int16 fft_bufferL[FFT_SIZE*2];
 Int16 fft_bufferR[FFT_SIZE*2];

 static Int16 out_delayL[FFT_SIZE/2];
 static Int16 out_delayR[FFT_SIZE/2];

Int16 window[FFT_SIZE];

Int16 znakL[FFT_SIZE];
Int16 znakR[FFT_SIZE];
Int16 XL[FFT_SIZE];
Int16 XR[FFT_SIZE];

Int16 sign(Int16 br)
{
	if(br < 0)
	{
		return -1;
	}else return 1;
}

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

	// DESNI KANAL
	for(i = 0; i < 2*N; i++)
	{
		fft_bufferR[i] = in[2*i + 1];									//UCITAVAMO OKVIR ZA DESNI KANAL
	}

	// ZADATAK 4 : REKONSTRUKCIJA
	if(BL == 0 && BR == 0)
	{
		Int16 k1 = round(2*N / 48000 * 100);			// PRVI OPSEG
		Int16 k2 = round(2*N / 48000 * 512);			// DRUGI OPSEG
		Int16 k3 = round(2*N / 48000 * 4096);			// TRECI OPSEG
		Int16 k4 = round(2*N / 48000 * 14336);			// CETVRTI OPSEG


		// ZA LEVI KANAL

		for(i = 0; i < k1; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], 0);
		}

		for(i = k1; i < k2; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], 8);
		}

		for(i = k2; i < k3; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], 12);
		}

		for(i = k3; i < k4; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], 6);
		}

		for(i = k4; i < 2*N; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], 0);
		}



		// ZA DESNI KANAl

		for(i = 0; i < k1; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], 0);
		}

		for(i = k1; i < k2; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], 8);
		}

		for(i = k2; i < k3; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], 12);
		}

		for(i = k3; i < k4; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], 6);
		}

		for(i = k4; i < 2*N; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], 0);
		}

	}
	else
	{

		// ZA LEVI KANAL

		for(i = 0; i < 2*N; i++)
		{
			fft_bufferL[i] = reconstructB(fft_bufferL[i], BL);				// REKONSTRUKCIJA
		}

		// ZA DESNI KANAL

		for(i = 0; i < 2*N; i++)
		{
			fft_bufferR[i] = reconstructB(fft_bufferR[i], BR);				// REKONSTRUKCIJA
		}
	}

	// 2 ZADATAK : VRACANJE IZ NELINEARNE OBRADE ZA LEVI KANAL
	for(i = 0; i < 2*N; i++)
	{
		XL[i] = fft_bufferL[i];
		znakL[i] = sign(XL[i]);
	}

	for(i = 0; i < 2*N; i++)
	{
		XL[i] = _smpy(XL[i], XL[i]);							//pow(XL, 2);
		XL[i] = znakL[i] * XL[i];
		fft_bufferL[i] = XL[i];
	}

	// 2 ZADATAK : VRACANJE IZ NELINEARNE OBRADE ZA DESNI KANAL
	for(i = 0; i < 2*N; i++)
	{
		XR[i] = fft_bufferR[i];
		znakR[i] = sign(XR[i]);
	}

	for(i = 0; i < 2*N; i++)
	{
		XR[i] = _smpy(XR[i], XR[i]);							//pow(XR, 2);
		XR[i] = znakR[i] * XR[i];
		fft_bufferR[i] = XR[i];
	}

	rifft(fft_bufferL, FFT_SIZE, NOSCALE);								// INVERZNA FFT

	for(i = 0; i < N; i++)
	{
		outL[i] = _smpy(fft_bufferL[i], window[i]) + _smpy(out_delayL[i], window[i + N]);
		outL[i] = outL[i] * 4;
		out_delayL[i] = fft_bufferL[i + N];								// DELAY CUVA DRUGIH N OBRIRAKA ZA NAREDNU ITERACIJU
	}


	rifft(fft_bufferR, FFT_SIZE, NOSCALE);								// INVERZNA FFT

	for(i = 0; i < N; i++)
	{
		outR[i] = _smpy(fft_bufferR[i], window[i]) + _smpy(out_delayR[i], window[i + N]);
		outR[i] = outR[i] * 4;
		out_delayR[i] = fft_bufferR[i + N];								// DELAY CUVA DRUGIH N OBRIRAKA ZA NAREDNU ITERACIJU
	}

}

