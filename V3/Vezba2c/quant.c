#include <math.h>
#include "tistdtypes.h"

Int16 quantB(float input, Uint16 B)
{
	/* Maximum value represented with B bits is 2^(B-1)-1 if we use sign integers */
	/* Minimum valueis -2^(B-1) */

	/* Calculate 2^(B-1) */
	float max_amp = (1L << (B - 1));

	/* Our interval is [-max_amp, max_amp) */

	/* Perform scaling */
	float output_float = floor(input * max_amp + 0.5);

	if(output_float == max_amp)
		output_float = max_amp-1;

	/* Convert from float to Int16 */
	Int16 output_int = output_float;

	return output_int;
}

float reconstructB(Int16 input, Uint16 B)
{
	float max_amp = 32768.0; // MAX INT 2^15

	float scaled_input = input << (16-B);

	float output = scaled_input / max_amp;

	return output; 
}


float snr(float* signal, float* noise, Uint16 n)
{
	/* Your code here*/

	float Ps = 0, Pe = 0;
	int i = 0;

	for (i = 0; i < n; i++)			// suma kvadratnih vrednosti signala
	{
		Ps += pow(signal[i], 2);
		Pe += pow(noise[i], 2);
	}

	Ps /= n;	// P = 1/N * suma kvadratnih vrednosti signala
	Pe /= n;

	return 10 * log10(Ps/Pe);
}


Int16 clipB(Int16 input, Uint16 B)
{
	Int16 max = (1L << (B-1)) - 1;
	Int16 min = - (1L << (B-1));
	Int16 output;

	if(input > max)
		output = max;
	else if (input < min)
		output = min;
	else
		output = input;

	return output;
}

Int16 wrapAroundB(Int16 input, Uint16 B)
{
		input <<= (16-B);
		input >>= (16-B);

		return input;
}


