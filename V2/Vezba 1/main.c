//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Vezba 2 - Generisanje signala.
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "ezdsp5535.h"
#include "math.h"
#include "gen_sinus.h"

#define PI 3.14159265

#define BUFFER_LENGTH 2048

float buffer[BUFFER_LENGTH];

/*
 *
 *  main( )
 *
 */
void main( void )
{

	/*printf("\n 1. Zadatak: \n");
	gen_sinus(1000, 10, 0.02, 0, buffer);
	gen_sinus(1000, 5, 0.05, PI/2, buffer);*/


	/*printf("\n 2. Zadatak: \n");
	gen_sinus_multiton(1000, 10, 0.05, 0.1, 0, buffer);
	gen_sinus_multiton(1000, 1, 0.1, 0.03, PI/2, buffer);*/


    /*printf("\n 3. Zadatak: \n");
	gen_log_sweep(1000, 5, 0.01, 0.1, 0, buffer);
	gen_lin_sweep(1000, 5, 0.01, 0.1, 0, buffer);*/


	/*printf("\n 4. Zadatak: \n");
	gen_sinus_table(1000, 10, 0.02, 0, buffer);
	gen_sinus_table(1000, 5, 0.05, PI/2, buffer);*/


	/*printf("\n 5. Zadatak: \n");
	gen_square(1000, 10, 0.05, 50, buffer);*/

	/*printf("\n 6. Zadatak: \n");
	gen_sinus_table(1000, 10, 0.02, 0, buffer);
	gen_sinus_table(1000, 5, 0.05, PI/2, buffer);*/

	printf("Kraj programa");

	SW_BREAKPOINT;



}

