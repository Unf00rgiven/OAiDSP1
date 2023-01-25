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
#include "gen_sinus.h"

#define N 2000

double sin_multitone_48kHz[N];
double sin_multitone_24kHz[N/2];

double freq_sweep_48kHz[N];
double freq_sweep_24kHz[N/2];
double freq_sweep_16kHz[N/3];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;

	/* Signal gen parameters */
    double sample_frequency = 48000.0;
    double amplitude = 10.0;
    double phase = 0.0;

    /* Multitione parameters*/
    double f0 = 1000.0;
    double dF = 5000.0;

    /* Log sweep parameters */
    double f1 = 1000.0;
    double f2 = 10000.0;

	printf("\n Vezba2 - Zadatak 1 \n");

	gen_sinus_multiton(N, amplitude, f0/sample_frequency, dF/sample_frequency, phase, sin_multitone_48kHz);
	
	for(i = 0; i < N/2; i++)
	{
		sin_multitone_24kHz[i] = sin_multitone_48kHz[2*i];
	}

	gen_log_sweep(N, amplitude, f1/sample_frequency, f2/sample_frequency, phase, freq_sweep_48kHz);

	/* Your code here */
	for(i = 0; i < N/2; i++)
	{
		freq_sweep_24kHz[i] = freq_sweep_48kHz[2*i];
	}

	for(i = 0; i < N/3; i++)
	{
		freq_sweep_16kHz[i] = freq_sweep_48kHz[3*i];
	}

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

