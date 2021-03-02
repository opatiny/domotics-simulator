#ifndef CONVERT_H
#define CONVERT_H

#include "messagesConfig.h"

// DEFINES

// STRUCTURES

// PUBLIC FUNCTIONS
int convert_to_MSG1(MSG message, int controllerCode, char address[45]);
int convert_to_MSG2(MSG message,
                    int controllerCode,
                    int eventCode,
                    char eventName[]);
int convert_to_MSG3(MSG message,
                    int controllerCode,
                    int eventCode,
                    u_int64_t timestamp,
                    double measurement);

#ifdef TEST_ENVIRONMENT
#endif  // TEST_ENVIRONMENT

#endif  // CONVERT_H
