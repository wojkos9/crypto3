#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>

int LOGLEVEL = 1;
#define dbg(lvl, ...) if (lvl <= LOGLEVEL) printf(__VA_ARGS__)

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

void primes_under(int n) {
  uint8_t *sieve = mksieve(n);

  int n_primes = 0;
  for (int p = 0; p <= n; p++) {
    if (!sieve[p]) {
      ++n_primes;
      dbg(2, "prime %d\n", p);
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
      dbg(2, "Twin primes: %d, %d\n", p, p+2);
    }
  }
  printf("Twin pairs %d - %d: %d\n", a, b, n_twins);
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
      dbg(2, "Mersenne prime %d (2^%d-1)\n", p, e);
    }
    x <<= 1;
    ++e;
  }

  printf("Mersenne primes <= %d: %d\n", n, n_primes);
  free(sieve);
}

void parse_opts(int argc, char *argv[]) {
  char c;
  while ((c = getopt(argc, argv, "v")) > 0) {
    switch(c) {
      case 'v':
        ++LOGLEVEL;
        break;
    }
  }
}

int main (int argc, char *argv[]) {
  parse_opts(argc, argv);
  primes_under(25);
  twin_primes(0, 2137);
  mersenne_primes(10000000);
  primes_under(10000);
  return 0;
}