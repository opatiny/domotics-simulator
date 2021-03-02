#ifndef SERVER_H
#define SERVER_H

// STRUCTURES

// PUBLIC FUNCTIONS
int initServer(void);
int closeServer(void);
int server(void);

#ifdef TEST_ENVIRONMENT
#endif  // TEST_ENVIRONMENT

#endif  // SERVER_H