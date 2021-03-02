#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "dataHandler.h"

// DEFINES

// PROTOTYPES
int incrementReadIndex(void);
int incrementWriteIndex(void);

// STRUCTURES INITIALIZATION
// defining an array of messages
MSG buffer[BUFFER_SIZE];
int writeIndex = 0;
int readIndex = 0;

// FUNCTIONS

/* write_MSG1(): write an MSG1 message to the data handler
  PARAMETERS:
    - controllerCode (int): code of the controller
    - address (char[]): the name / address of the controller (text)
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int write_MSG1(int controllerCode, char address[]) {
  MSG msg1 = "";

  convert_to_MSG1(msg1, controllerCode, address);
  stpcpy(buffer[writeIndex], msg1);
  incrementWriteIndex();

  return 0;
}

/* write_MSG2(): write an MSG2 message to the data handler
  PARAMETERS:
    - controllerCode (int): code of the controller
    - eventCode (int): code of the event
    - eventName (char[]): the name of the event (text)
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int write_MSG2(int controllerCode, int eventCode, char eventName[]) {
  MSG msg2 = "";

  convert_to_MSG2(msg2, controllerCode, eventCode, eventName);
  stpcpy(buffer[writeIndex], msg2);
  incrementWriteIndex();

  return 0;
}

/* write_MSG3(): write an MSG3 message to the data handler
  PARAMETERS:
    - controllerCode (int): code of the controller
    - eventCode (int): code of the event
        - timestamp (u_int_64): timestamp  in seconds(since beginning of
          simulation)
    - measurement (double): value of the measurement in special float format
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int write_MSG3(int controllerCode,
               int eventCode,
               u_int64_t timestamp,
               double measurement) {
  MSG msg3 = "";

  convert_to_MSG3(msg3, controllerCode, eventCode, timestamp, measurement);
  stpcpy(buffer[writeIndex], msg3);
  incrementWriteIndex();

  return 0;
}

/* read_buffer_MSG(): copies the msg at readIndex to the given variable, then
  erases the message from the buffer PARAMETERS:
    - message (MSG): pointer on an array of chars
  RETURNS:
    - (int): possible error message
  Author: Océane Patiny
 */
int read_buffer_MSG(MSG message) {
  strcpy(message, buffer[readIndex]);
  buffer[readIndex][0] = '\0';  // erasing message that was read to avoid
                                // looping over and reading it twice
  incrementReadIndex();
  return 0;
}

int incrementReadIndex(void) {
  // handling edge effect
  if (readIndex == BUFFER_SIZE - 1) {
    readIndex = 0;
  } else {
    readIndex++;
  }

  return 0;
}

int incrementWriteIndex(void) {
  // handling edge effect
  if (writeIndex == BUFFER_SIZE - 1) {
    writeIndex = 0;
  } else {
    writeIndex++;
  }

  return 0;
}