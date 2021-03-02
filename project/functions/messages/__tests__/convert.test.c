#define TEST_ENVIRONMENT

#include <string.h>

#include "../../../lib/testcases.h"
#include "../convert.h"

int test_convert_to_MSG1(void) {
  int NB_CASES_FAILING = 0;

  MSG message;

  convert_to_MSG1(message, 443, "a controller address street 4.5");

  char expected[] = "1 443              a controller address street 4.5";

  shouldBeEqual_s(&NB_CASES_FAILING, message, expected);
  return checkTest(NB_CASES_FAILING);
}

int test_convert_to_MSG2(void) {
  int NB_CASES_FAILING = 0;

  MSG message;

  convert_to_MSG2(message, 443, 512, "temperature");

  char expected[] = "2 443 512         temperature";

  shouldBeEqual_s(&NB_CASES_FAILING, message, expected);
  return checkTest(NB_CASES_FAILING);
}

int test_convert_to_MSG3(void) {
  int NB_CASES_FAILING = 0;

  MSG message;

  convert_to_MSG3(message, 543, 2, 12345, -5.7);

  char expected[] = "3 543   2     12345    -5.700";

  shouldBeEqual_s(&NB_CASES_FAILING, message, expected);
  return checkTest(NB_CASES_FAILING);
}
