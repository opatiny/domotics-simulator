#ifndef WEATHER_H
#define WEATHER_H

// STRUCTURES
typedef struct weather_temperature {
  double current;    // in °C
  double offset;     // in °C
  double amplitude;  // in °C
  double phase;      // in degrees
} WEATHER_TEMPERATURE;

typedef struct weather_luminosity {
  double current;       // in lux
  double max;           // in lux (typically 20000 lux at midday with clear sky)
  double min;           // in lux (typically <0 lux at night)
  double intervals[4];  // intervals for each segment in seconds
} WEATHER_LUMINOSITY;

typedef struct weather {
  WEATHER_TEMPERATURE temperature;
  WEATHER_LUMINOSITY luminosity;  // in cd
} WEATHER;

// PUBLIC FUNCTIONS
int updateWeatherLuminosity(u_int32_t currentTimeOfDay, int index);
int updateWeatherTemperature(u_int32_t currentTimeOfDay, int index);

double getWeatherLuminosity(int index);
double getWeatherTemperature(int index);

#ifdef TEST_ENVIRONMENT
int luminosityModel(u_int32_t currentTimeOfDay, WEATHER_LUMINOSITY* luminosity);
int setTwilightLuminosity(u_int32_t currentTimeOfDay,
                          WEATHER_LUMINOSITY* luminosity);
double line(double x, double slope, double offset);
double noisySinusoid(double offset,
                     double amplitude,
                     double period,
                     double time,
                     double phase,
                     double noiseFunction(double));
#endif  // TEST_ENVIRONMENT

#endif // WEATHER_H
