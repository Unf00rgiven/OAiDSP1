/*
 * processing.c
 *
 *  Created on: 29.02.2016.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.com)
 */

#include "processing.h"
#include "fir.h"
#include "filter_coeff.h"

static Int16 filtered[1024] = {0};
static Int16 history[N_COEFF];
static Uint16 state = 0;

static Int16 history_poly[M_FACTOR][N_COEFF_P] = {0};
static Uint16 state_poly[M_FACTOR] = {0, 0};


void downsample(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i, j;

	for(i = 0, j = 0; i< N; i += M, j++)
	{
		output[j] = input[i];
	}
}

void decimate(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i = 0;

	for(i = 0; i< N; i++)
	{
		filtered[i] = fir_circular(input[i], lp_filter, history, N_COEFF, &state);
	}
	downsample(filtered, output, M, N);
}


void calculate_poly_coeffs(Int16 M)
{
	int i, j, k;
	for(i = 0, j=0; i < N_COEFF; i+=M, j++)
	{
		for(k = 0; k < M; k++)
		{
			lp_filter_poly[k][j] = lp_filter[i+k];
		}
	}

}

void decimate_poly(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i = 0, j = 0, k = 0;
	for(j=0; j < N_COEFF_P;j++)
		{
			for(k = 0; k < M; k++)
			{
				history_poly[k][j] = 0;
			}
		}

	output[0] = fir_circular(input[i], lp_filter_poly[0], history_poly[0], N_COEFF_P, &state_poly[0]);

	for(i = M, j = 1; i< N; i+=M, j++)
	{
		output[j] = fir_circular(input[i], lp_filter_poly[0], history_poly[0], N_COEFF_P, &state_poly[0]);
		for(k = 1; k < M; k++ )
			output[j] += fir_circular(input[i-k], lp_filter_poly[k], history_poly[k], N_COEFF_P, &state_poly[k]);
	}
}


void upsample(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
}

void interpolate(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
}

void resample(Int16 *input, Int16 *output, int L, int M, int N)
{
	/* your code here... */
}

void interpolate_poly(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
}

