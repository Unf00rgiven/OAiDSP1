//////////////////////////////////////////////////////////////////////////////
// * File name: decode.c
// *
// *
// * Description: Audio Decoder
// * Course: OAiS DSP1
// * Year: 2020
// *
// * Author: <TO DO - add student name and index>
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
 Int16 fft_buffer[FFT_SIZE*2];

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
void decode(Int16* in, Int16* outL, Int16* outR, Int16 N);
