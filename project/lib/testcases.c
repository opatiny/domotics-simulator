#include <math.h>
#include <string.h>

#include "testcases.h"

int shouldBeEqual_i(int* nbCasesFailing, int value, int expected) {
  if (value != expected) {
    printf("    got: %i, expected: %i \n", value, expected);
    (*nbCasesFailing)++;
    return 1;
  }
  return 0;
}

int shouldBeEqual_lu(int* nbCasesFailing, u_int64_t value, u_int64_t expected) {
  if (value != expected) {
    printf("    got: %lu, expected: %lu \n", value, expected);
    (*nbCasesFailing)++;
    return 1;
  }
  return 0;
}

int shouldBeEqual_lf(int* nbCasesFailing,
                     double value,
                     double expected,
                     double maxError) {
  if (fabs(value - expected) >
      maxError) {  // fabs() is the absolute value function for doubles
    printf("    got: %lf, expected: %lf \n", value, expected);
    (*nbCasesFailing)++;
    return 1;
  }
  return 0;
}

int shouldBeEqual_s(int* nbCasesFailing, char value[], char expected[]) {
  if (strcmp(value, expected)) {
    printf("%10s%50s\n", "got:", value);
    printf("%10s%50s\n", "expected:", expected);
    (*nbCasesFailing)++;

    return 1;
  }
  return 0;
}

int shouldBeGreaterThan_d(int* nbCasesFailing, double value, double expected) {
  if (!(value > expected)) {
    printf("    got: %lf, expected greater than: %lf \n", value, expected);
    (*nbCasesFailing)++;
    return 1;
  }
  return 0;
}

int shouldBeSmallerThan_d(int* nbCasesFailing, double value, double expected) {
  if (!(value < expected)) {
    printf("    got: %lf, expected smaller than: %lf \n", value, expected);
    (*nbCasesFailing)++;
    return 1;
  }
  return 0;
}

int checkTest(int nbCasesFailing) {
  if (nbCasesFailing) {
    return TEST_FAILING;
  }

  return TEST_PASSING;
}