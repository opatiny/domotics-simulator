#ifndef AQUARIUM_H
#define AQUARIUM_H

// STRUCTURES
typedef struct aquarium {
  double currentPH;            // in °C
  double luminosityImpact;     // from 0 to 1
  double luminosityThreshold;  // in lux
  double pumpImpact;           // from 0 to 1
  double pumpValue;            // value of the pump, set in controllers
} AQUARIUM;

// PUBLIC FUNCTIONS
int updatePH(int index);

int setPumpValue(int index, double value);
double getPH(int index);

#ifdef TEST_ENVIRONMENT
int phModel(AQUARIUM* aquarium, double roomLuminosity);
#endif  // TEST_ENVIRONMENT

#endif  // AQUARIUM_H