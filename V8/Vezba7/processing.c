/*
 * processing.c
 *
 *  Created on: 13.12.2020.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.uns.ac.rs)
 */

#include "processing.h"
#include "Dsplib.h"
#include "ezdsp5535_aic3204_dma.h"
#include <math.h>


#define PI 3.1415926535
#define FFT_SIZE (2*AUDIO_IO_SIZE)

#pragma DATA_ALIGN(fft_buffer,256)
static Int16 fft_buffer[FFT_SIZE];
static Int16 in_delay[FFT_SIZE/2];
static Int16 out_delay[FFT_SIZE/2];

Int16 window[FFT_SIZE];

void processing(Int16* in, Int16* out, Int16 N)
{
	/* Your code here */
}



void init_vorbis_window()
{
  int i;
  double t;

  for (i = 0; i < FFT_SIZE/2; i++) {
    t = sin(0.5 * PI * (i + 0.5) / (FFT_SIZE/2));
    window[i] = 32767 * sin(0.5 * PI * t * t);
    window[FFT_SIZE-1-i] = window[i];
  }
}
