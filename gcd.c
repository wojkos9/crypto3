#include "utils.h"
#include <stdio.h>


int gcd(int a, int b) {
  int r;
  while (a % r) {
    r = a % b;
    printf("%d ", r);
    a = b;
    b = r;
  }
  puts("");
  return b > 0 ? b : -b;
}


int main() {
  pair pairs[] = {
    {141, 111},
    {208, 264},
    {57998, 162432},
    {785437, 543889},
    };
  for (int i = 0; i < sizeof(pairs) / sizeof(pair); i++) {
    pair p = pairs[i];
    printf("gcd (%d, %d) = %d\n", p.a, p.b, gcd(p.a, p.b));
  }
  return 0;
}