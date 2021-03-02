#define TEST_ENVIRONMENT

#include "../../lib/testcases.h"
#include "../aquarium.h"

int test_phModel(void) {
  int NB_CASES_FAILING = 0;

  AQUARIUM aquarium1 = {.currentPH = 7,
                        .luminosityImpact = 1,
                        .luminosityThreshold = 10000,
                        .pumpImpact = 0,
                        .pumpValue = 10};
  phModel(&aquarium1, 20000);
  shouldBeGreaterThan_d(&NB_CASES_FAILING, aquarium1.currentPH, 7);

  AQUARIUM aquarium2 = {.currentPH = 7,
                        .luminosityImpact = 1,
                        .luminosityThreshold = 10000,
                        .pumpImpact = 0,
                        .pumpValue = 10

  };
  phModel(&aquarium2, 5000);
  shouldBeSmallerThan_d(&NB_CASES_FAILING, aquarium2.currentPH, 7);

  AQUARIUM aquarium3 = {.currentPH = 7,
                        .luminosityImpact = 0,
                        .luminosityThreshold = 10000,
                        .pumpImpact = 1,
                        .pumpValue = 10

  };
  phModel(&aquarium3, 20000);
  shouldBeGreaterThan_d(&NB_CASES_FAILING, aquarium3.currentPH, 7);

  return checkTest(NB_CASES_FAILING);
}
