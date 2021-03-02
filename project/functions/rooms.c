#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "rooms.h"
#include "weather.h"

// PROTOTYPES
int roomTemperatureModel(double* currentTemperature,
                         double weatherTemperature,
                         double weatherImpact,
                         double controllerValue,
                         double controllerImpact);
int roomLuminosityModel(double* currentLuminosity,
                        double weatherLuminosity,
                        double weatherImpact);

// STRUCTURES INITIALIZATION
// defining all parameters for rooms 1 and 2
ROOM rooms[] = {{.temperature = {.current = 15,
                                 .weatherImpact = 0.2,
                                 .controllerImpact = 0.5},
                 .luminosity = {.current = 0.25,
                                .weatherImpact = 0.5,
                                .controllerImpact = 0.8}},
                {.temperature = {.current = 20,
                                 .weatherImpact = 0.25,
                                 .controllerImpact = 0.6},
                 .luminosity = {.current = 0.25,
                                .weatherImpact = 0.6,
                                .controllerImpact = 0.9}}};

int weatherIndex;  // this is an option that comes from the scheduler

// FUNCTIONS
// in our case, "index" of the rooms can be 0 or 1 (they are 2 rooms)

/* setRoomsWeatherIndex(): sets weatherIndex to the right value (this function
  is used in the scheduler)
  PARAMETERS:
    -  value (int): index of the weather struct to work with
  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int setRoomsWeatherIndex(int value) {
  weatherIndex = value;
  return 0;
}

/* updateRoomTemperature(): update temperature of a given room
  PARAMETERS:
    -  index (int): index of the room in rooms array
  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int updateRoomTemperature(int index) {
  double weatherTemperature = getWeatherTemperature(weatherIndex);  // in °C

  roomTemperatureModel(&rooms[index].temperature.current, weatherTemperature,
                       rooms[index].temperature.weatherImpact,
                       rooms[index].temperature.controllerValue,
                       rooms[index].temperature.controllerImpact);

  return 0;
}

/* updateRoomLuminosity(): update luminosity of a given room
  PARAMETERS:
    -  index (int): index of the room in rooms array
  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int updateRoomLuminosity(int index) {
  double weatherLuminosity = getWeatherLuminosity(weatherIndex);

  roomLuminosityModel(&rooms[index].luminosity.current, weatherLuminosity,
                      rooms[index].luminosity.weatherImpact);
  return 0;
}

double getRoomTemperature(int index) {
  return rooms[index].temperature.current;
}

double getRoomLuminosity(int index) {
  return rooms[index].luminosity.current;
}

int setTemperatureControllerValue(int index, double value) {
  rooms[index].temperature.controllerValue = value;
  return 0;
}

// PRIVATE FUNCTIONS

/* roomTemperatureModel(): updates a room's temperature depending on various
  parameters

  PARAMETERS:
    -  currentTemperature (double*): initial room temperature in °C
    -  weatherTemperature (double): weather temperature in °C
    -  weatherImpact (double): impact of weather temperature on room
  temperature [0,1]
    -  controllerTemperature (double): initial room temperature in °C
    -  controllerImpact (double): impact of controller temperature on room
  temperature [0,1]

  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int roomTemperatureModel(double* currentTemperature,
                         double weatherTemperature,
                         double weatherImpact,
                         double controllerValue,
                         double controllerImpact) {
  *currentTemperature =
      *currentTemperature +
      weatherImpact * (weatherTemperature - *currentTemperature) +
      controllerImpact * controllerValue;
  return 0;
}

/* roomLuminosityModel(): updates a room's luminosity depending on various
  parameters

  PARAMETERS:
    -  currentLuminosity (double*): initial room luminosity in lux
    -  weatherLuminosity (double): weather luminosity in lux
    -  weatherImpact (double): impact of weather luminosity on room
  luminosity [0,1]

  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int roomLuminosityModel(double* currentLuminosity,
                        double weatherLuminosity,
                        double weatherImpact) {
  *currentLuminosity = weatherLuminosity * weatherImpact;
  return 0;
}