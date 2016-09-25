#include <stdio.h>
#include "sieve.h"

int main ()
{
	llu_t n = 15485863989898931;

	printf ("mr     - %d\n", is_prime_mr (n));
	printf ("simple - %d\n", is_prime (NULL, n));

	return 0;
}
