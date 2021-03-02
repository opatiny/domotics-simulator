#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "weather.h"

// data for Lausanne
WEATHER weathers[] = {
    {
        .temperature = {.offset = 23, .amplitude = 5, .phase = -150},  // summer
        .luminosity = {.max = 100000,  // bright sunlight
                       .min = 0.25,
                       .intervals = {4 * 3600, 5 * 3600, 21.5 * 3600,
                                     23 * 3600}},
    },
    {.temperature = {.offset = 5, .amplitude = 5, .phase = -150},  // winter
     .luminosity = {.max = 20000,
                    .min = 0.25,
                    .intervals = {7 * 3600, 8.25 * 3600, 16.8 * 3600,
                                  18 * 3600}}}

};

// PROTOTYPES
int luminosityModel(u_int32_t currentTimeOfDay, WEATHER_LUMINOSITY* luminosity);
int setTwilightLuminosity(u_int32_t currentTimeOfDay,
                          WEATHER_LUMINOSITY* luminosity);
double line(double x, double slope, double offset);
double randomTenPercentNoise(double amplitude);
double noisySinusoid(double offset,
                     double amplitude,
                     double period,
                     double time,
                     double phase,
                     double noiseFunction(double));

// PUBLIC FUNCTIONS

/* updateWeatherLuminosity(): updates current weather luminosity
  PARAMETERS:
    -  currentTime (int): current time in [s]
    -  index (int): index of the weather struct to modify in "weathers"
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int updateWeatherLuminosity(u_int32_t currentTimeOfDay, int index) {
  luminosityModel(currentTimeOfDay, &(weathers[index].luminosity));
  return 0;
}

/* updateWeatherTemperature(): updates current weather temperature
  PARAMETERS:
    -  currentTime (int): current time in [s]
    -  index (int): index of the weather struct to modify in "weathers"
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int updateWeatherTemperature(u_int32_t currentTimeOfDay, int index) {
  double offset = weathers[index].temperature.offset;
  double amplitude = weathers[index].temperature.amplitude;
  double period = 60 * 60 * 24;  // number of seconds in one day
  double time = (double)currentTimeOfDay;
  double phase = weathers[index].temperature.phase;

  weathers[index].temperature.current = noisySinusoid(
      offset, amplitude, period, time, phase, &randomTenPercentNoise);

  return 0;
}

double getWeatherLuminosity(int index) {
  return weathers[index].luminosity.current;
}

double getWeatherTemperature(int index) {
  return weathers[index].temperature.current;
}

// PRIVATE FUNCTIONS
/* luminosityModel(): set luminosity.current variable of luminosity struct
                      instance
  PARAMETERS:
    -  currentTimeOfDay (u_int32_t): current time of day in seconds
    - luminosity (WEATHER_LUMINOSITY*): pointer on luminosity struct instance
  RETURNS:
    - int (possible error message)
  Author: Océane Patiny
 */
int luminosityModel(u_int32_t currentTimeOfDay,
                    WEATHER_LUMINOSITY* luminosity) {
  if (currentTimeOfDay < luminosity->intervals[0]) {
    luminosity->current = luminosity->min;
  } else if (luminosity->intervals[0] <= currentTimeOfDay &&
             currentTimeOfDay < luminosity->intervals[1]) {
    setTwilightLuminosity(currentTimeOfDay, luminosity);  // sunrise
  } else if (luminosity->intervals[1] <= currentTimeOfDay &&
             currentTimeOfDay < luminosity->intervals[2]) {
    luminosity->current = luminosity->max;
  } else if (luminosity->intervals[2] <= currentTimeOfDay &&
             currentTimeOfDay < luminosity->intervals[3]) {
    setTwilightLuminosity(currentTimeOfDay, luminosity);  // sunset
  } else if (luminosity->intervals[3] <= currentTimeOfDay) {
    luminosity->current = luminosity->min;
  } else {
    return 1;
  }
  return 0;
}

/* setTwilightLuminosity(): sets current luminostity for sunset and sunrise
                            times of day
  PARAMETERS:
    -  currentTimeOfDay (u_int32_t): current time of day in [s]
    -  luminosity (LUMINOSITY*): pointer on luminosity struct
    - dayPhase (char): option to specify wheather it is
  RETURNS:
    - (double)
  Author: Océane Patiny
 */
int setTwilightLuminosity(u_int32_t currentTimeOfDay,
                          WEATHER_LUMINOSITY* luminosity) {
  double slope = 0;
  double offset = 0;
  double time = 0;  // this is a kind of relative time for the line() function

  // slope is computed here so that the stored data is not redundant and so that
  // there is a memory/CPU tradeoff

  // verifying if current time of day is in sunrise interval
  if (luminosity->intervals[0] <= currentTimeOfDay &&
      currentTimeOfDay < luminosity->intervals[1]) {
    offset = luminosity->min;
    slope = (luminosity->max - luminosity->min) /
            (luminosity->intervals[1] - luminosity->intervals[0]);
    time = currentTimeOfDay - luminosity->intervals[0];
  } else if (luminosity->intervals[2] <= currentTimeOfDay &&
             currentTimeOfDay < luminosity->intervals[3]) {
    // verifying if current time of day is in sunset interval
    offset = luminosity->max;
    slope = (luminosity->min - luminosity->max) /
            (luminosity->intervals[3] - luminosity->intervals[2]);
    time = currentTimeOfDay - luminosity->intervals[2];
  } else {
    // currentTimeOfDay is not in sunrise or sunset interval
    return 1;
  }

  luminosity->current = line(time, slope, offset);

  return 0;
}

/* line(): evaluates an affine function at a given point
  PARAMETERS:
    -  x (double): point at which to evaluate the function
    -  slope (double): slope of the line
    -  offset (double): y offset of the line
  RETURNS:
    - (double)
  Author: Océane Patiny
 */
double line(double x, double slope, double offset) {
  return slope * x + offset;
}

/* noisySinusoid(): returns the value of a noisy sinusoidal signal at a given
  time
  PARAMETERS:
    -  offset (double): constant value added to the sinusoid
    -  amplitude (double): amplitude of the signal
    -  period (double): period of the sinusoid in [s]
    -  time (double): time in [s]
        -  phase (double): phase in [°]
    -  controllerImpact (*)(double): pointer on function that generates noise
       based on amplitude
  RETURNS:
    - (double)
  Author: Océane Patiny
 */
double noisySinusoid(double offset,
                     double amplitude,
                     double period,
                     double time,
                     double phase,
                     double noiseFunction(double)) {
  double omega = 2 * M_PI / period;
  double noise = noiseFunction(amplitude);
  double result =
      offset + amplitude * sin(omega * time + phase * M_PI / 180) + noise;
  return result;
}

// returns random value between 0 and 10% of amplitude
double randomTenPercentNoise(double amplitude) {
  return amplitude * (2 * (double)rand() / RAND_MAX - 1) / 10;
}

/* gaussianNoise(): returns a value to which is added a gaussian noise
  computed using Box-Muller method (1SD)
  PARAMETERS:
    -  mu (double): value to which the noise will be added (peak of the Bell
       curve)
    -  sigma (double): one standard deviation for mu
  RETURNS:
    - (double)
  Author: Océane Patiny
 */
double gaussianNoise(double mu, double sigma) {
  double value1 = (double)rand() / RAND_MAX;
  double value2 = (double)rand() / RAND_MAX;

  double rho = sqrt(-2 * log(value1));
  double theta = 2 * M_PI * value1;
  double X = rho * cos(theta);

  return mu + sigma * X;
}