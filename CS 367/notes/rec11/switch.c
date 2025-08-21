#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long do_switch(long opt) {
  long val = 0;
  switch(opt) {
    case 1: val = 0x10;
            break;
    case 2: val = 0x200;
            break;
    case 4: val = 0x4000;
            break;
    case 5:
    case 6: val = 0x60;
            break;
    default: val = 0;
             break;
  }
  return val * val;
}

int main() {
  srand(time(NULL));
  long opt = rand()%7;
  printf("Switching on %ld\n", opt);
  long ret = do_switch(opt);
  printf("Returned %ld\n", ret);
  return 0;
}
