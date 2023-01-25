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

#pragma DATA_ALIGN(fft_bufferL,4)
#pragma DATA_ALIGN(fft_bufferR,4)
static Int16 fft_bufferL[FFT_SIZE];
static Int16 fft_bufferR[FFT_SIZE];

static Int16 in_delayL[FFT_SIZE/2];
static Int16 in_delayR[FFT_SIZE/2];

Int16 window[FFT_SIZE];

void init_vorbis_window(Int16 N)
{
  int i;
  double t;

  for (i = 0; i < N; i++)
  {
    t = sin(0.5 * PI * (i + 0.5) / N);
    window[i] = 32767 * sin(0.5 * PI * t * t);
    window[2*N-1-i] = window[i];
  }
}


Int16 sign(Int16 br)
{
	if(br > 0 )
	{
		return 1;
	}else return -1;
}

Int16 XL[FFT_SIZE];
Int16 XR[FFT_SIZE];
Int16 znakL[FFT_SIZE];
Int16 znakR[FFT_SIZE];

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

	for(i = 0; i < 2*N; i++)
	{
		fft_bufferL[i] = _smpy(fft_bufferL[i], window[i]);
	}

	rfft(fft_bufferL, FFT_SIZE, SCALE);							// FFT

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

	// ZADATAK 2 : NELINEARNA OBRADA
	for(i = 0; i < 2*N; i++)
	{
		XL[i] = fft_bufferL[i];
		XR[i] = fft_bufferR[i];

		znakL[i] = sign(XL[i]);
		znakR[i] = sign(XR[i]);

		if(znakL[i] == -1)
		{
			XL[i] *= (-1);
		}

		if(znakR[i] == -1)
		{
			XR[i] *= (-1);
		}
	}

	sqrt_16(XL, XL, FFT_SIZE);
	sqrt_16(XR, XR, FFT_SIZE);

	for(i = 0; i < 2*N; i++)
	{
		XL[i] *= znakL[i];
		fft_bufferL[i] = XL[i];
		XR[i] *= znakR[i];
		fft_bufferR[i] = XR[i];
	}

	// ZADATAK 4 : KVANTIZACIJA
	if(BL == 0 && BR == 0)
	{
		Int16 k1 = round(FFT_SIZE / 48000 * 100);			// PRVI OPSEG
		Int16 k2 = round(FFT_SIZE / 48000 * 512);			// DRUGI OPSEG
		Int16 k3 = round(FFT_SIZE / 48000 * 4096);			// TRECI OPSEG
		Int16 k4 = round(FFT_SIZE / 48000 * 14336);			// CETVRTI OPSEG

		// ZA LEVI KANAL

		for(i = 0; i < 2*N; i++)
		{
			if(i < k1)
			{
				fft_bufferL[i] = 0;
			}
			else if(i < k2)
			{
				fft_bufferL[i] = quantB(fft_bufferL[i], 8);
			}
			else if(i < k3)
			{
				fft_bufferL[i] = quantB(fft_bufferL[i], 12);
			}
			else if(i < k4)
			{
				fft_bufferL[i] = quantB(fft_bufferL[i], 6);
			}
			else
			{
				fft_bufferL[i] = 0;
			}
		}

			// ZA DESNI KANAL

		for(i = 0; i < 2*N; i++)
		{
			if(i < k1)
			{
				fft_bufferR[i] = 0;
			}
			else if(i < k2)
			{
				fft_bufferR[i] = quantB(fft_bufferR[i], 8);
			}
			else if(i < k3)
			{
				fft_bufferR[i] = quantB(fft_bufferR[i], 12);
			}
			else if(i < k4)
			{
				fft_bufferR[i] = quantB(fft_bufferR[i], 6);
			}
			else
			{
				fft_bufferR[i] = 0;
			}
		}
	}
	else
	{
		// OBICNA KVANTIZACIJA ZA LEVI KANAl

		for(i = 0; i < 2*N; i++)
		{
			fft_bufferL[i] = quantB(fft_bufferL[i], BL);
		}

		// OBICNA KVANTIZACIJA ZA DESNI KANAl

		for(i = 0; i < 2*N; i++)
		{

			fft_bufferR[i] = quantB(fft_bufferR[i], BR);
		}
	}

	// SPAJANJE LEVOG I DESNOG KANALA
	for(i = 0; i < 2*N; i++)
	{
		out[2*i] = fft_bufferL[i];
		out[2*i + 1] = fft_bufferR[i];
	}
}


