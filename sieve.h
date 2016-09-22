#ifndef SIEVE_H
#define SIEVE_H

typedef unsigned long long	llu_t;
typedef long long int		lli_t;

typedef struct
{
	unsigned char* left_;
	unsigned char* right_; 
	llu_t size_;
}sieve;


sieve*  create_sieve (llu_t sieve_size);
bool    is_prime     (const sieve* s, llu_t number);
bool	is_prime_mr	 (llu_t number);
void    free_sieve	 (sieve* s);

#endif //SIEVE_H
