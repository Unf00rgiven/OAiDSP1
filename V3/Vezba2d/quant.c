#include <math.h>
#include "tistdtypes.h"

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


