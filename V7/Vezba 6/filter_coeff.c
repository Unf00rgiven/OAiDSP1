/*
 * filter_coeff.c
 *
 *  Created on: 29.02.2016.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.com)
 */

#include "filter_coeff.h"

Int16 lp_filter[N_COEFF+4] = { 83, 83, 0, -282, -687, -791, 0, 1979, 4725, 7161, 8137, 7161, 4725, 1979, 0, -791, -687, -282, 0, 83, 83, 0, 0, 0, 0 };
Int16 lp_filter_poly[M_FACTOR][N_COEFF_P];
