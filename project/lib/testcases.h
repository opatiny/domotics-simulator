#ifndef TESTS_LIB

#define TEST_PASSING 0
#define TEST_FAILING 1

#include <stdio.h>
#include <stdlib.h>

int shouldBeEqual_i(int* nbCasesFailing, int value, int expected);
int shouldBeEqual_lu(int* nbCasesFailing, u_int64_t value, u_int64_t expected);
int shouldBeEqual_lf(int* nbCasesFailing,
                     double value,
                     double expected,
                     double maxError);
int shouldBeEqual_s(int* nbCasesFailing, char value[], char expected[]);

int shouldBeGreaterThan_d(int* nbCasesFailing, double value, double expected);
int shouldBeSmallerThan_d(int* nbCasesFailing, double value, double expected);

int checkTest(int nbCasesFailing);
#endif  // !TESTS_LIB
