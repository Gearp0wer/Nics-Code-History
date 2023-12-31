#include <stdio.h>
#include <stdlib.h>
#include "common_structs.h"
#include "common_definitions.h"
#include "common_functions.h"
#include "tinysf.h"

// Prototypes
void test_negate();

// Function Definitions
int main() {
  test_negate();
  return 0;
}

// Example testing function for negateTinySF
void test_negate() {
  tinysf_s val = 0x0700;
  printf(" val = 0x%04x\n", val);
  val = negateTinySF(val);
  printf("-val = 0x%04x\n", val);
}
