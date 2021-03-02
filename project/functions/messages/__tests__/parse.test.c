#define TEST_ENVIRONMENT

#include <string.h>

#include "../../../lib/testcases.h"
#include "../parse.h"

int test_parse_MSG1(void) {
  int NB_CASES_FAILING = 0;

  MSG1 result;

  char message[] = "1 443              a controller address street 4.5";

  parse_MSG1(message, &result);

  shouldBeEqual_i(&NB_CASES_FAILING, result.type, 1);
  shouldBeEqual_i(&NB_CASES_FAILING, result.controllerCode, 443);
  shouldBeEqual_s(&NB_CASES_FAILING, result.address,
                  "a controller address street 4.5");

  char message2[] = "15443aaaaaaaaaaaaaaa controller address street 4.5";

  parse_MSG1(message2, &result);

  shouldBeEqual_i(&NB_CASES_FAILING, result.type, 1);
  shouldBeEqual_i(&NB_CASES_FAILING, result.controllerCode, 5443);
  shouldBeEqual_s(&NB_CASES_FAILING, result.address,
                  "aaaaaaaaaaaaaaa controller address street 4.5");

  return checkTest(NB_CASES_FAILING);
}

int test_parse_MSG2(void) {
  int NB_CASES_FAILING = 0;

  MSG2 result;

  char message[] = "2 2445567    room temperature";

  parse_MSG2(message, &result);

  shouldBeEqual_i(&NB_CASES_FAILING, result.type, 2);
  shouldBeEqual_i(&NB_CASES_FAILING, result.controllerCode, 244);
  shouldBeEqual_i(&NB_CASES_FAILING, result.eventCode, 5567);
  shouldBeEqual_s(&NB_CASES_FAILING, result.eventName, "room temperature");

  char message2[] = "2 244   7room 123 temperature";

  parse_MSG2(message2, &result);

  shouldBeEqual_i(&NB_CASES_FAILING, result.type, 2);
  shouldBeEqual_i(&NB_CASES_FAILING, result.controllerCode, 244);
  shouldBeEqual_i(&NB_CASES_FAILING, result.eventCode, 7);
  shouldBeEqual_s(&NB_CASES_FAILING, result.eventName, "room 123 temperature");

  return checkTest(NB_CASES_FAILING);
}

int test_parse_MSG3(void) {
  int NB_CASES_FAILING = 0;

  MSG3 result;

  char message[] = "36543   21234567890    -5.700";

  parse_MSG3(message, &result);

  shouldBeEqual_i(&NB_CASES_FAILING, result.type, 3);
  shouldBeEqual_i(&NB_CASES_FAILING, result.controllerCode, 6543);
  shouldBeEqual_i(&NB_CASES_FAILING, result.eventCode, 2);
  shouldBeEqual_lu(&NB_CASES_FAILING, result.timestamp, 1234567890);
  shouldBeEqual_lf(&NB_CASES_FAILING, result.measurement, -5.7, 0);
  return checkTest(NB_CASES_FAILING);
}
