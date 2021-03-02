#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

// DEFINES

// PROTOTYPES

// STRUCTURES INITIALIZATION

// FUNCTIONS

/* parse_MSG1(): parses an MSG1 message and places the data in the given MSG1
  structure
  PARAMETERS:
    - stringMessage (MSG): array of chars containing the message to parse
    - parsedMessage (MSG1*): pointer on an instance of MSG1
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int parse_MSG1(MSG stringMessage, MSG1* parsedMessage) {
  int scanResult =
      sscanf(stringMessage, "%1i%4i %[^\t\n]", &(parsedMessage->type),
             &(parsedMessage->controllerCode), parsedMessage->address);

  if (scanResult != 3) {
    return 1;
  }

  return 0;
}

/* parse_MSG2(): parses an MSG2 message and places the data in the given MSG2
  structure
  PARAMETERS:
    - stringMessage (MSG): array of chars containing the message to parse
    - parsedMessage (MSG2*): pointer on an instance of MSG2
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int parse_MSG2(MSG stringMessage, MSG2* parsedMessage) {
  char controllerCode[5] = {'\0'};
  char eventCode[5] = {'\0'};

  int scanResult =
      sscanf(stringMessage, "%1i%4c%4c %[^\t\n]", &(parsedMessage->type),
             controllerCode, eventCode, parsedMessage->eventName);

  if (scanResult != 4) {
    return 1;
  }

  parsedMessage->controllerCode = atoi(controllerCode);
  parsedMessage->eventCode = atoi(eventCode);

  return 0;
}

/* parse_MSG3(): parses an MSG3 message and places the data in the given MSG3
  structure
  PARAMETERS:
    - stringMessage (MSG): array of chars containing the message to parse
    - parsedMessage (MSG3*): pointer on an instance of MSG3
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int parse_MSG3(MSG stringMessage, MSG3* parsedMessage) {
  char controllerCode[5] = {'\0'};
  char eventCode[5] = {'\0'};

  int scanResult =
      sscanf(stringMessage, "%1i%4c%4c%10lu%10lf", &(parsedMessage->type),
             controllerCode, eventCode, &(parsedMessage->timestamp),
             &(parsedMessage->measurement));

  if (scanResult != 5) {
    return 1;
  }

  parsedMessage->controllerCode = atoi(controllerCode);
  parsedMessage->eventCode = atoi(eventCode);

  return 0;
}
