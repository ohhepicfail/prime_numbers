#include <stdio.h>
#include "sieve.h"

int main ()
{
	llu_t number = 1000000000;

	for (llu_t n = number; n < 100 + number; n++)
	{
		if (is_prime (NULL, n) != is_prime_mr (n))
			printf ("\n---!!!---fail---!!!--- --%llu\t%d\t%d\n", n, is_prime (NULL, n), is_prime_mr (n));
	}

	return 0;
}
