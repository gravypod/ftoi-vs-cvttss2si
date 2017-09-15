#include <stdio.h>
#include <stdlib.h>

#define IEEE_FLT_MANTISSA_BITS  23
#define IEEE_FLT_EXPONENT_BITS  8
#define IEEE_FLT_EXPONENT_BIAS  127
#define IEEE_FLT_SIGN_BIT       31

int ftoi(float f)
{
	// Source from idlib/math/Math.h; Please read ID_LICENSE.txt
	int i, s, e, m, shift;
	i = *((int *)(&f));
	s = i >> IEEE_FLT_SIGN_BIT;
	e = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
	m = ( i & ( ( 1 << IEEE_FLT_MANTISSA_BITS ) - 1 ) ) | ( 1 << IEEE_FLT_MANTISSA_BITS );
	shift = e - IEEE_FLT_MANTISSA_BITS;
	return ( ( ( ( m >> -shift ) | ( m << shift ) ) & ~( e >> 31 ) ) ^ s ) - s;
}


int main(int argc, char **argv)
{
	if (argc == 1)
		exit(1);

	int number = atoi(argv[1]);
	float f = number / 0.1f;

	int   *ints   = malloc(sizeof(int)   * number);
	float *floats = malloc(sizeof(float) * number);

	for (int i = 0; i < number; i++)
		ints[i] = ftoi(floats[i] = f);

}
