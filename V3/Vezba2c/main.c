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

#include <cstdio>
#include "ezdsp5535.h"

#include "quant.h"
#include "signal.h"

#define N SIGNAL_LENGTH

Int16 quant_sine[N];

float reconstructed_sine[N];
float quantisation_noise[N];

float sin_wrap[N];
float sin_clip[N];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;
	float SNR;
    printf("\n OAiS DSP 1 - Vezba 2 \n");

	/* 4-bit Quantisation */
	for(i = 0; i < N; i++)
	{
		quant_sine[i] = quantB(p_signal[i], 16);
	}

		
	/* 4-bit Reconstruct signal */
	for(i = 0; i < N; i++)
	{
		reconstructed_sine[i] = reconstructB(quant_sine[i], 16);
	}

	// sum
	for(i = 0; i < N; i++)
	{
		quantisation_noise[i] = (reconstructed_sine[i] - p_signal[i]);
	}

	for(i = 0; i < N; i++)
	{
		sin_wrap[i] = reconstructB(wrapAroundB(quant_sine[i], 15), 15);
		sin_clip[i] = reconstructB(clipB(quant_sine[i], 15), 15);
	}


	SNR = snr(p_signal, quantisation_noise, N);
	printf("4-bit quantisation SNR: %f\n", SNR);

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

