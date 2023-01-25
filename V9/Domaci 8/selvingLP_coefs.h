/*
 * selvingLP_coefs.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Ognjen Stojisavljevic RA 155/2019
 */

#ifndef SELVINGLP_COEFS_H_
#define SELVINGLP_COEFS_H_


Int16 selvingLP_coef[4] = {22938, -32767, 32767, -22938};
Int16 selvingHP_coef[4] = {-22938, -32767, 32767, 22938};

Int16 selvingSecondOrder1_coef[6] = {206464, 0, 1, 1, 0, 206464};	// alfa1 je 6.301, beta je 0
Int16 selvingSecondOrder2_coef[6] = {5177, 0, 1, 1, 0, 5177};	// alfa2 je 0.158, beta je 0


#endif /* SELVINGLP_COEFS_H_ */
