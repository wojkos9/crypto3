#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#define LOGLEVEL 3
#define dbg(lvl, ...) if (a <= LOGLEVEL) printf(__VA_ARGS__)

uint8_t *mksieve(int n) {
  uint8_t *sieve = malloc(n+1);
  bzero(sieve, n);
  sieve[0] = 1;
  sieve[1] = 1;

  for (int i = 2; i*i <= n; i++) {
    if (!sieve[i]) {
      for (int j = i+i; j <= n; j += i) {
        sieve[j] = 1;
      }
    }
  }
  return sieve;
}

void primes_summary(int n) {
  uint8_t *sieve = mksieve(n);

  int n_primes = 0;
  for (int p = 0; p <= n; p++) {
    if (!sieve[p]) {
      ++n_primes;
      printf("prime %d\n", p);
    }
  }

  printf("Primes <= %d: %d\n", n, n_primes);

  free(sieve);
}

void twin_primes(int a, int b) {
  uint8_t *sieve = mksieve(b);
  int n_twins = 0;
  for (int p = a; p <= b-2; p++) {
    if (!sieve[p] && !sieve[p+2]) {
      ++n_twins;
      printf("Twin primes: %d, %d\n", p, p+2);
    }
  }
  printf("Twin pairs: %d\n", n_twins);
  free(sieve);
}

void mersenne_primes(int n) {
  uint8_t *sieve = mksieve(n);

  int n_primes = 0;
  int x = 1;
  int e = 0;
  while(x < n) {
    int p = x-1;
    if (!sieve[p]) {
      ++n_primes;
      printf("Mersenne prime %d (2^%d-1)\n", p, e);
    }
    x <<= 1;
    ++e;
  }

  printf("Mersenne primes <= %d: %d\n", n, n_primes);
  free(sieve);
}

int main (int argc, char *argv[]) {
  primes_summary(25);
  twin_primes(0, 1000);
  mersenne_primes(10000000);
  return 0;
}