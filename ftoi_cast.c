#include <stdio.h>
#include <stdlib.h>

int ftoi(float f)
{
	return (int) f;
}


int main(int argc, char **argv)
{
	int number = atoi(argv[1]);
	float f = number / 0.1f;

	int   *ints   = malloc(sizeof(int)   * number);
	float *floats = malloc(sizeof(float) * number);

	for (int i = 0; i < number; i++)
		ints[i] = ftoi(floats[i] = f);
}
