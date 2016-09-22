#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "sieve.h"

llu_t find_prime (const sieve* s, llu_t number, llu_t n);

int main ()
{
    llu_t n = 1000000;
    llu_t size = n * (log (n) + log (log (n)));
    sieve* s = create_sieve (size);
    llu_t mil_idx = find_prime (s, n, size);
    printf ("%llu\n", mil_idx);

    free_sieve (s);
    return 0;
}

llu_t find_prime (const sieve* s, llu_t number, llu_t n)
{
    assert (s);

    llu_t counter = 0;
    llu_t i = 0;
    for (i = 0; i < n; i++)
    {
        if (is_prime (s, i))
            counter++;

        if (counter == number)
            break;
    }

    return (counter == number) ? i : 0;
}

