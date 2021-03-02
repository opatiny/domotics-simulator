#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

// STRUCTURES
typedef struct user_options {
  const int nbTics;              // defines the simulation length
  const int ticLength;           // in seconds -> accuracy of the simulation
  const int weather;             // can be LAUSANNE_SUMMER or LAUSANNE_WINTER
  const bool showOutputData;     // 0 or 1
  const bool showControlValues;  // 0 or 1

} USER_OPTIONS;

// PUBLIC FUNCTIONS
int Scheduler(void);

#endif  // SCHEDULER_H
