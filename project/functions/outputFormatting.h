#ifndef OUTPUT_FORMATTING_H
#define OUTPUT_FORMATTING_H

#include <stdbool.h>

// DEFINES
#define NB_ROOMS_OUTPUT 2
#define NB_AQUARIUMS_OUTPUT 1

// STRUCTURES
typedef struct data {
  int TIC;
  double weatherTemperature;
  double weatherLuminosity;
  double roomsTemperature[NB_ROOMS_OUTPUT];
  double roomsLuminostiy[NB_ROOMS_OUTPUT];
  double aquariumsPH[NB_AQUARIUMS_OUTPUT];
  double temperatureControllers[NB_ROOMS_OUTPUT];
  double luminosityControllers[NB_ROOMS_OUTPUT];
  double phControllers[NB_AQUARIUMS_OUTPUT];
  // options
  bool showControlValues;  // 0 or 1
  bool exportData;         // 0 or 1
} DATA;

// PUBLIC FUNCTIONS
void printHeader(DATA* data);
void printDataLine(DATA* data);

// COLORS FOR TERMINAL OUTPUT (source:
// https://stackoverflow.com/questions/1961209/making-some-text-in-printf-appear-in-green-and-red)
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

#endif  // OUTPUT_FORMATTING_H
