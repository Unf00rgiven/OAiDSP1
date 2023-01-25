//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 6
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: Ognjen Stojisavljevic RA 155/2019
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////


#include "tistdtypes.h"
#include <cstdio>
#include "ezdsp5535.h"
#include "math.h"
#include "signal.h"
#include "filter_coeff.h"
#include "processing.h"

/*
 *
 *  main( )
 *
 */

#define M 4
Int16 outputBuffer1[SIGNAL1_LENGTH/M];

#define L 4
Int16 outputBuffer2[SIGNAL2_LENGTH*L];

void main( void )
{

	printf("\n Vezba 6 - Interpolacija i decimacija \n");

	/* Your code here */
	//1
	//downsample(signal1, outputBuffer1, M, SIGNAL1_LENGTH);

	//2
	//decimate(signal1, outputBuffer1, M, SIGNAL1_LENGTH);

	//3
	//upsample(signal2, outputBuffer2, L, SIGNAL2_LENGTH);
		
	//4
	//interpolate(signal2, outputBuffer2, L, SIGNAL2_LENGTH);

	//5
	//resample(signal2, outputBuffer2, 3, 4, SIGNAL2_LENGTH);
	//resample(signal2, outputBuffer2, 4, 3, SIGNAL2_LENGTH);

	//6
	//calculate_poly_coeffs(M);
	//decimate_poly(signal1, outputBuffer1, M, SIGNAL1_LENGTH);

	//7
	//calculate_poly_coeffs(L);
	//interpolate_poly(signal2, outputBuffer2, L, SIGNAL2_LENGTH);

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

