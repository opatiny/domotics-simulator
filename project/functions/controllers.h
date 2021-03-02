#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <stdbool.h>

// STRUCTURES
typedef struct pump {
  double currentValue;  // in ??
  double phThreshold;   // PH from 0 to 14
  double factor;        // no dimension
  int identifier;       // unique identifier of the controller
} PUMP;

typedef struct temperature_controller {
  double currentValue;             // in °C
  double minTemperatureThreshold;  // in °C
  double maxTemperatureThreshold;  // in °C
  double factor;                   // no dimension
  int identifier;                  // unique identifier of the controller

} TEMPERATURE_CONTROLLER;

// PUBLIC FUNCTIONS
int announceControllers(void);

int temperatureControl(int index, u_int64_t currentTime);
int phControl(int index, u_int64_t currentTime);

double getTemperatureControlValue(int index);
double getPhControlValue(int index);

#ifdef TEST_ENVIRONMENT
int temperatureControlModel(double roomTemperature, TEMPERATURE_CONTROLLER* tc);
int phControlModel(double currentPH, PUMP* pump);
#endif  // TEST_ENVIRONMENT

#endif  // CONTROLLERS_H
