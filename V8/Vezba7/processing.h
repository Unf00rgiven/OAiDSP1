/*
 * processing.c
 *
 *  Created on: 13.12.2020.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.uns.ac.rs)
 */

#include "tistdtypes.h"

#ifndef PROCESSING_H_
#define PROCESSING_H_

void processing(Int16* in, Int16* out, Int16 N);

void init_vorbis_window();

#endif /* PROCESSING_H_ */
