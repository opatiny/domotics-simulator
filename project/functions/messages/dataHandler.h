#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#include "messagesConfig.h"
#include "parse.h"

// PUBLIC FUNCTIONS

int write_MSG1(int controllerCode, char address[]);
int write_MSG2(int controllerCode, int eventCode, char eventName[]);
int write_MSG3(int controllerCode,
               int eventCode,
               u_int64_t timestamp,
               double measurement);

int read_buffer_MSG(MSG message);

#ifdef TEST_ENVIRONMENT
#endif  // TEST_ENVIRONMENT

#endif  // DATA_HANDLER_H
