#include <stdio.h>
#include "sieve.h"

int main ()
{
	for (llu_t number = 100; number < 10000000000000; number *= 10)
	{
		for (llu_t n = number; n < 100 + number; n++)
			if (is_prime (NULL, n) != is_prime_mr (n))
				printf ("\n---!!!---fail---!!!--- --%llu\t%d\t%d\n", n, is_prime (NULL, n), is_prime_mr (n));
		printf (".");
	}


	return 0;
}
