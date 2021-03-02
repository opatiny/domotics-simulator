#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Scheduler.h"
#include "aquarium.h"
#include "controllers.h"
#include "outputFormatting.h"
#include "rooms.h"
#include "server.h"
#include "weather.h"

// DEFINES

// defining the number of tics to wait between each call of the functions
#define WEATHER_LIGHT_SAMPLING 1
#define WEATHER_TEMPERATURE_SAMPLING 1
#define ROOMS_TEMPERATURE_SAMPLING 1
#define ROOMS_LIGHT_SAMPLING 1
#define AQUARIUM_PH_SAMPLING 1
#define TEMPERATURE_CONTROL_SAMPLING 1
#define LIGHT_CONTROL_SAMPLING 1
#define PH_CONTROL_SAMPLING 1
#define SERVER_SAMPLING 6

// indexes in weather structures array
#define LAUSANNE_SUMMER 0
#define LAUSANNE_WINTER 1

// number of instances of different structures
#define NB_ROOMS 2
#define NB_AQUARIUMS 1

// STRUCTURES INITIALIZATION
// simulation user options (the basic time unit is one second)
USER_OPTIONS options = {.nbTics = 24,
                        .ticLength = 60 * 60,  //  in seconds
                        .weather = LAUSANNE_WINTER,
                        .showOutputData = 1,
                        .showControlValues = 1};
DATA outputData;

// FUNCTIONS

/* Scheduler(): project main function handling all threads
  PARAMETERS:
    -  void
  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int Scheduler(void) {
  // INITALIZATION AND CONFIGURATION
  // setting options for output data
  outputData.showControlValues = options.showControlValues;
  outputData.exportData = 0;
  // set the weather struct to use in rooms
  setRoomsWeatherIndex(options.weather);
  // initialize server (open log files)
  initServer();
  // announce controllers to data handler
  announceControllers();

  // SCHEDULER
  if (options.showOutputData) {
    printf("Welcome to this basic domotics simulator.\n\n");

    printf("The TIC length is %i seconds.\n\n", options.ticLength);

    printHeader(&outputData);
  }

  for (int currentTIC = 1; currentTIC < options.nbTics + 1; currentTIC++) {
    outputData.TIC = currentTIC;

    u_int32_t currentTimeOfDay = currentTIC * options.ticLength %
                                 (24 * 3600);  // current time of day in seconds
    // has to be on 32 bites because 24*3600 = 84'600 > 65'535
    u_int64_t currentTime = currentTIC * options.ticLength;

    if (currentTIC == 1 || !(currentTIC % WEATHER_LIGHT_SAMPLING)) {
      updateWeatherLuminosity(currentTimeOfDay, options.weather);
      double weatherLuminosity = getWeatherLuminosity(options.weather);
      outputData.weatherLuminosity = weatherLuminosity;
    }
    if (!(currentTIC % WEATHER_TEMPERATURE_SAMPLING)) {
      updateWeatherTemperature(currentTimeOfDay, options.weather);
      double weatherTemperature = getWeatherTemperature(options.weather);
      outputData.weatherTemperature = weatherTemperature;
    }
    if (!(currentTIC % ROOMS_TEMPERATURE_SAMPLING)) {
      for (int i = 0; i < NB_ROOMS; i++) {
        updateRoomTemperature(i);
        double roomTemperature = getRoomTemperature(i);
        if (i < NB_ROOMS_OUTPUT) {
          outputData.roomsTemperature[i] = roomTemperature;
        }
      }
    }
    if (!(currentTIC % ROOMS_LIGHT_SAMPLING)) {
      for (int i = 0; i < NB_ROOMS; i++) {
        updateRoomLuminosity(i);
        double roomLuminostiy = getRoomLuminosity(i);
        if (i < NB_ROOMS_OUTPUT) {
          outputData.roomsLuminostiy[i] = roomLuminostiy;
        }
      }
    }
    if (!(currentTIC % AQUARIUM_PH_SAMPLING)) {
      for (int i = 0; i < NB_AQUARIUMS; i++) {
        updatePH(i);
        double aquariumPH = getPH(i);
        if (i < NB_AQUARIUMS_OUTPUT) {
          outputData.aquariumsPH[i] = aquariumPH;
        }
      }
    }
    if (!(currentTIC % TEMPERATURE_CONTROL_SAMPLING)) {
      for (int i = 0; i < NB_ROOMS; i++) {
        temperatureControl(i, currentTime);
        double temperatureControlValue = getTemperatureControlValue(i);
        if (i < NB_ROOMS_OUTPUT) {
          outputData.temperatureControllers[i] = temperatureControlValue;
        }
      }
    }
    if (!(currentTIC % LIGHT_CONTROL_SAMPLING)) {
      // no controller implemented
    }
    if (!(currentTIC % PH_CONTROL_SAMPLING)) {
      for (int i = 0; i < NB_AQUARIUMS; i++) {
        phControl(i, currentTime);
        double phControlValue = getPhControlValue(i);
        if (i < NB_AQUARIUMS_OUTPUT) {
          outputData.phControllers[i] = phControlValue;
        }
      }
    }
    if (!(currentTIC % SERVER_SAMPLING)) {
      server();
    }

    if (options.showOutputData) {
      printDataLine(&outputData);
    }
  }

  closeServer();

  return 0;
}
