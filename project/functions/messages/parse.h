#ifndef PARSE_H
#define PARSE_H

#include "messagesConfig.h"

// DEFINES

// STRUCTURES

// PUBLIC FUNCTIONS
int parse_MSG1(MSG stringMessage, MSG1* parsedMessage);
int parse_MSG2(MSG stringMessage, MSG2* parsedMessage);
int parse_MSG3(MSG stringMessage, MSG3* parsedMessage);

#endif  // PARSE_H
