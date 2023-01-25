#pragma once


#define F1_COEFFS 33
#define constint = 32767
#define fs = 0.05

Int16 filter1_coeffs[F1_COEFFS] =
{
		// TO DO: Add filter coeffs calculated in task No.2
				 1169,
		          831,
		         -862,
		        -1455,
		          165,
		         1817,
		          867,
		        -1707,
		        -2110,
		          909,
		         3380,
		          890,
		        -4478,
		        -4669,
		         5222,
		        19582,
		        26430,
		        19582,
		         5222,
		        -4669,
		        -4478,
		          890,
		         3380,
		          909,
		        -2110,
		        -1707,
		          867,
		         1817,
		          165,
		        -1455,
		         -862,
		          831,
		         1169
};

#define F2_COEFFS 121

Int16 filter2_coeffs[F2_COEFFS] =
{
       // TO DO: Add filter coeffs calculated in task No.3
       155,
          327,
           16,
         -330,
         -197,
          236,
          333,
          -64,
         -382,
         -141,
          321,
          322,
         -160,
         -424,
          -64,
          409,
          291,
         -270,
         -453,
           36,
          497,
          233,
         -396,
         -464,
          164,
          581,
          145,
         -538,
         -451,
          325,
          661,
           17,
         -700,
         -406,
          529,
          733,
         -166,
         -891,
         -314,
          801,
          795,
         -439,
        -1132,
         -148,
         1190,
          846,
         -878,
        -1481,
          168,
         1850,
          883,
        -1739,
        -2148,
          926,
         3442,
          906,
        -4561,
        -4755,
         5318,
        19941,
        26915,
        19941,
         5318,
        -4755,
        -4561,
          906,
         3442,
          926,
        -2148,
        -1739,
          883,
         1850,
          168,
        -1481,
         -878,
          846,
         1190,
         -148,
        -1132,
         -439,
          795,
          801,
         -314,
         -891,
         -166,
          733,
          529,
         -406,
         -700,
           17,
          661,
          325,
         -451,
         -538,
          145,
          581,
          164,
         -464,
         -396,
          233,
          497,
           36,
         -453,
         -270,
          291,
          409,
          -64,
         -424,
         -160,
          322,
          321,
         -141,
         -382,
          -64,
          333,
          236,
         -197,
         -330,
           16,
          327,
          155
};


Int16 iir_notch_coeffs[6] =
{
       // TO DO: Add filter coeffs calculated in task No.5
		32767,
		-31163,
		32676,
		32676,
		-29605,
		29572
};

Int16 iir_notch_coeffsmatrix[3][6] =
{
	{32767, -31163, 32676, 32676, -29605, 29572},
	{32767, -31163, 32676, 32676, -29605, 29572},
	{32767, -31163, 32676, 32676, -29605, 29572}

};
