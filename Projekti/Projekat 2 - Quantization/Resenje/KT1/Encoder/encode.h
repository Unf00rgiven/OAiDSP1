//////////////////////////////////////////////////////////////////////////////
// * File name: encode.h
// *
// *
// * Description: Audio Decoder
// * Course: OAiS DSP1
// * Year: 2021
// *
// * Author: <Ognjen stojisavljevic RA155/2019>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include "tistdtypes.h"

#ifndef ENCODE_H_
#define ENCODE_H_


// FRAME_SIZE = 2(kanala) * 2(dvostruka dužina okvira zbog preklopi-saberi) * AUDIO_IO_SIZE = 512
#define FRAME_SIZE (4*AUDIO_IO_SIZE)

void init_vorbis_window(Int16 N);

// TODO: Deklarisati funkciju za enkodovanje
void encode(Int16* inL, Int16* inR, Int16* out, Int16 N, Uint16 BL, Uint16 BR);

#endif /* ENCODE_H_ */
