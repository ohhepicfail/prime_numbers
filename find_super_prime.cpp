#include <stdio.h>
#include <assert.h>
#include <cmath>
#include <new>
#include "sieve.h"

typedef unsigned char digit_t;

unsigned find         (unsigned n);
unsigned build_number (digit_t* digits, unsigned n);
unsigned next_number  (digit_t* digits, unsigned n);


int main ()
{
    unsigned n = 9;
    printf ("%u\n", find (n));

    return 0;
}


unsigned find (unsigned n)
{
    assert (n < 10);

    while (n > 3)
    {
        digit_t* digits = new (std::nothrow) digit_t[n];
        assert (digits);
        
        unsigned digits_sum = 0;
        for (unsigned i = 0; i < n; i++)
        {
            digits[i] = n - i;
            digits_sum += digits[i];
        }

        if (digits_sum % 3 == 0)
        {
            n--;
            continue;
        }

        unsigned suspect = build_number (digits, n);
        while (suspect)
        {
            if (is_prime (NULL, suspect))
                return suspect;

            suspect = next_number (digits, n);
        }

        n--;
        delete[] digits;
    }

    return 0;
}

unsigned build_number (digit_t* digits, unsigned n)
{
    assert (digits);
    assert (n > 1);

    unsigned res = 0;
    for (unsigned i = 0; i < n; i++)
        res = res * 10 + digits[i];

    return res;
}

unsigned next_number (digit_t* digits, unsigned n)
{
    assert (digits);
    assert (n > 1);

    unsigned left_idx = n;
    for (unsigned i = n - 1; i > 0; i--)
        if (digits[i] < digits[i - 1])
        {
            left_idx = i - 1;
            break;
        }

    unsigned right_idx = n;
    for (size_t i = n - 1; i > 0; i--)
        if (digits[i] < digits[left_idx])
        {
            right_idx = i;
            break;
        }

    if (left_idx == n || right_idx == n)
        return 0;

    digit_t tmp       = digits[left_idx];
    digits[left_idx]  = digits[right_idx];
    digits[right_idx] = tmp;
    right_idx = n - 1;
    left_idx++;
    while (left_idx < right_idx)
    {
        tmp               = digits[left_idx];
        digits[left_idx]  = digits[right_idx];
        digits[right_idx] = tmp;
        left_idx++;
        right_idx--;
    }

    unsigned res = build_number (digits, n);
    return res;
}