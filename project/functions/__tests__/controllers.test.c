#define TEST_ENVIRONMENT

#include "../../lib/testcases.h"
#include "../controllers.h"

int test_temperatureControlModel(void) {
  int NB_CASES_FAILING = 0;
  TEMPERATURE_CONTROLLER tc = {.currentValue = 0,
                               .minTemperatureThreshold = 10,
                               .maxTemperatureThreshold = 20,
                               .factor = 1};

  temperatureControlModel(15, &tc);
  shouldBeEqual_lf(&NB_CASES_FAILING, tc.currentValue, 0, 0);

  temperatureControlModel(5, &tc);
  shouldBeGreaterThan_d(&NB_CASES_FAILING, tc.currentValue, 0);

  temperatureControlModel(25, &tc);
  shouldBeSmallerThan_d(&NB_CASES_FAILING, tc.currentValue, 0);

  return checkTest(NB_CASES_FAILING);
}

int test_phControlModel(void) {
  int NB_CASES_FAILING = 0;

  PUMP pump1 = {.currentValue = 0, .phThreshold = 5, .factor = 10};

  phControlModel(3, &pump1);
  shouldBeGreaterThan_d(&NB_CASES_FAILING, pump1.currentValue, 0.0);

  phControlModel(8, &pump1);
  shouldBeEqual_lf(&NB_CASES_FAILING, pump1.currentValue, 0.0, 0.0);

  return checkTest(NB_CASES_FAILING);
}
