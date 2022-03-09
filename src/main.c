#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define ALPHABETSIZE       (26 + 26 + 10 + 2)
static inline char whichchar(unsigned i) {
  if (i < 26)
    return 'A' + i;
  else if (i < (26 + 26))
    return 'a' + (i - 26);
  else if (i < (26 + 26 + 10))
    return '0' + (i - (26 + 26));
  else if (i < (ALPHABETSIZE))
    return ':' + (i - (26 + 26 + 10));
  else
    return '\0';
}

int main(int argc, char **argv) {
  if(argc != 2) {
    printf("Usage: %s <npasses>\n", argv[0]);
    printf("npasses: Number of passes of get calls");
    exit(1);
  }
  unsigned npasses = (unsigned)strtoul(argv[1], NULL, 10);

  cache_init();
  char key[16], value[64];

  for(int i = 0; i < NITEMS; i++) {
    int tmp = i;
    int j;
    for(j = 0; j < NCHARS; j++) {
      key[j] = whichchar(tmp % ALPHABETSIZE);
      tmp /= ALPHABETSIZE;
    }
    key[j] = '\0';

    cache_set(key, j, "hell1hell2hell3hell4hell5", 25);
  }

  for(int j = 0; j < npasses; j++) {
    for(int i = 0; i < NITEMS; i++) {
      int tmp = i;
      int j;
      for(j = 0; j < NCHARS; j++) {
        key[j] = whichchar(tmp % ALPHABETSIZE);
        tmp /= ALPHABETSIZE;
      }
      key[j] = '\0';

      cache_get(key, j, value, 64);
    }
  }
  // dump_cache();

  return 0;
}
