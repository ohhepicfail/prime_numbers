#include "sieve.h"
#include <malloc.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>


static inline sieve*   allocate_mem_for_sieve  (llu_t sieve_size);
static inline void     check_and_set           (sieve* s, llu_t idx);
static inline bool     check_lbit              (const sieve* s, llu_t idx);
static inline bool     check_rbit              (const sieve* s, llu_t idx);
static inline void     set_lbit                (sieve* s, llu_t idx);
static inline void     set_rbit                (sieve* s, llu_t idx);
static inline lli_t    pow_mod                 (llu_t base, llu_t pow, llu_t mod);
static inline bool     mr_witness              (llu_t number, llu_t s, llu_t d, unsigned a);

static inline sieve*  allocate_mem_for_sieve  (llu_t sieve_size)
{
    sieve* s = (sieve*) calloc (1, sizeof (sieve));
    assert (s);

    if (sieve_size % 6 == 1)
        s->size_ =sieve_size / 6;
    else if (sieve_size % 6 == 5)
        s->size_ =sieve_size / 6 + 1;
    else
        s->size_ = sieve_size / 6;

    if (s->size_ % CHAR_BIT)
        s->size_ = s->size_ / CHAR_BIT + 1;
    else
        s->size_ = s->size_ / CHAR_BIT;

    s->left_  = (unsigned char*) calloc (s->size_, sizeof (unsigned char));
    s->right_ = (unsigned char*) calloc (s->size_, sizeof (unsigned char));
    assert (s->left_);
    assert (s->right_);

    return s;
}


static inline void check_and_set (sieve* s, llu_t idx)
{
    assert (s);
    assert (s->left_);
    assert (s->right_);

    if ( ! check_lbit (s, idx))
    {
        llu_t offset = 6 * (idx + 1) - 1;
        for (llu_t j = 2 * offset; j / 6 < s->size_ * CHAR_BIT; j += offset)
        {
            if (j % 6 == 5)
                set_lbit (s, j / 6);
            else if (j % 6 == 1)
                set_rbit (s, j / 6 - 1);
        }
    }
    if ( ! check_rbit (s, idx))
    {
        llu_t offset = 6 * (idx + 1) + 1;
        for (llu_t j = 2 * offset; j / 6 < s->size_ * CHAR_BIT; j += offset)
        {
            if (j % 6 == 5)
                set_lbit (s, j / 6);
            else if (j % 6 == 1)
                set_rbit (s, j / 6 - 1);
        }
    }
}


sieve* create_sieve (llu_t sieve_size)
{
    sieve* s = allocate_mem_for_sieve (sieve_size);
    assert (s);
    assert (s->left_);
    assert (s->right_);

    for (llu_t i = 0; i < s->size_ * CHAR_BIT; i++)
        check_and_set (s, i);

    return s;
}


bool is_prime (const sieve* s, llu_t number)
{
    bool prime = true;
    if (number < 2)
        prime = false;
    else if (number == 2 || number == 3)
        prime = true;
    else if (number % 2 == 0 || number % 3 == 0)
        prime = false;
    else if (s && 6 * s->size_ * CHAR_BIT + 1 >= number)
    {
        assert (s->left_);
        assert (s->right_);
        
        if (number % 6 == 5)
            prime = ! check_lbit (s, number / 6);
        else if (number % 6 == 1)
            prime = ! check_rbit (s, number / 6 - 1);
        else
            prime = false;
    }
    else if (s && 6 * s->size_ * CHAR_BIT + 1 > sqrt (number))
    {
        assert (s->left_);
        assert (s->right_);

        prime = true;

        for (llu_t i = 0; i < s->size_ * CHAR_BIT; i++)
        {
            if (check_lbit (s, i) != 0 && number % (6 * i - 1) == 0)
            {
                prime = 0;
                break;
            }
            else if (check_rbit (s, i) != 0 && number % (6 * i + 1) == 0)
            {
                prime = 0;
                break;
            }
            else if (6 * i + 1 > sqrt (number))
                break;
        }
    }
    else
    {
        for (llu_t i = 6; i <= sqrt (number) + 1; i += 6)
            if (number % (i - 1) == 0 || number % (i + 1) == 0)
            {
                prime = false;
                break;
            }
            else
                prime = true;
    }

    return prime;
}

bool is_prime_mr (llu_t number)
{
    if (number == 2)
        return true;
    else if (number == 1 || number % 2 == 0)
        return false;

    llu_t s = 0;
    llu_t d = number - 1;
    for (; d % 2 == 0; s++)
        d /= 2;

    #define W( a )              mr_witness (number, s, d, a)
    if (number < 2047)
        return W (2);
    else if (number < 1373653)
        return W (2) && W (3);
    else if (number < 9080191)
        return W (31) && W (73);
    else if (number < 25326001)
        return W (2) && W (3) && W (5);
    else if (number < 3215031751)
        return W (2) && W (3) && W (5) && W (7);
    else if (number < 4759123141)
        return W (2) && W (7) && W (61);
    else if (number < 1122004669633)
        return W (2) && W (13) && W (23) && W (1662803);
    else if (number < 2152302898747)
        return W (2) && W (3) && W (5) && W (7) && W (11);
    else if (number < 3474749660383)
        return W (2) && W (3) && W (5) && W (7) && W (11) && W (13);
    else if (number < 341550071728321)
        return W (2) && W (3) && W (5) && W (7) && W (11) && W (13) && W (17);
    else if (number < 3825123056546413051)
        return W (2) && W (3) && W (5) && W (7) && W (11) && W (13) && W (17) && W (19) && W (23);
    else
        return W (2) && W (3) && W (5) && W (7) && W (11) && W (13) && W (17) && W (19) && W (23) && W (29) && W (31) && W (37); 
    #undef W
}

static inline bool mr_witness (llu_t number, llu_t s, llu_t d, unsigned a)
{
    if (pow_mod (a, d, number) != 1)
    {
        llu_t r = 0;
        for (; r < s; r++)
            if (pow_mod (a, (llu_t) pow (2, r) * d, number) == number - 1)
                break;

        if (r == s)
            return false;
    } 

    return true;
}

static inline lli_t pow_mod (llu_t base, llu_t pow, llu_t mod)
{
    llu_t tmp = 1;

    while (pow) 
    {
        if (pow % 2 == 0) 
        {
            pow /= 2;
            base = (base * base) % mod;
        }
        else 
        {
            pow--;;
            tmp = (tmp * base) % mod;
        }
    }
    return tmp;
}

void free_sieve (sieve* s)
{
    assert (s);
    assert (s->left_);
    assert (s->right_);

    free (s->left_);
    free (s->right_);
    free (s);
}

static inline bool check_lbit (const sieve* s, llu_t idx)
{
    assert (s);
    assert (s->left_);

    return (s->left_ [idx / CHAR_BIT] >> (idx % CHAR_BIT)) & 1;
}

static inline bool check_rbit (const sieve* s, llu_t idx)
{
    assert (s);
    assert (s->right_);

    return (s->right_ [idx / CHAR_BIT] >> (idx % CHAR_BIT)) & 1;
}

static inline void set_lbit (sieve* s, llu_t idx)
{
    assert (s);
    assert (s->left_);

    s->left_ [idx / CHAR_BIT] |= 1 << (idx % CHAR_BIT);
}

static inline void set_rbit (sieve* s, llu_t idx)
{
    assert (s);
    assert (s->right_);

    s->right_ [idx / CHAR_BIT] |= 1 << (idx % CHAR_BIT);
}
