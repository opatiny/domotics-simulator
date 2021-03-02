#ifndef ROOMS_H
#define ROOMS_H

// DEFINES

// STRUCTURES
typedef struct room_temperature {
  double current;           // in °C
  double weatherImpact;     // from 0 to 1
  double controllerValue;   // in ??
  double controllerImpact;  // from 0 to 1
} ROOM_TEMPERATURE;

typedef struct room_luminosity {
  double current;           // in lux
  double weatherImpact;     // from 0 to 1
  double controllerImpact;  // from 0 to 1 -> will not be implemented
} ROOM_LUMINOSITY;

typedef struct room {
  ROOM_TEMPERATURE temperature;
  ROOM_LUMINOSITY luminosity;
} ROOM;

// PUBLIC FUNCTIONS

int setRoomsWeatherIndex(int value);

int updateRoomTemperature(int roomNumber);
int updateRoomLuminosity(int roomNumber);

double getRoomTemperature(int roomNumber);
double getRoomLuminosity(int roomNumber);
int setTemperatureControllerValue(int index, double value);

#ifdef TEST_ENVIRONMENT
int roomTemperatureModel(double* currentTemperature,
                         double weatherTemperature,
                         double weatherImpact,
                         double controllerValue,
                         double controllerImpact);

int roomLuminosityModel(double* currentLuminosity,
                        double weatherLuminosity,
                        double weatherImpact);
#endif  // TEST_ENVIRONMENT

#endif  // ROOMS_H
