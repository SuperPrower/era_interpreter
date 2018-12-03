#ifndef ERA_STATUS_H
#define ERA_STATUS_H

// TODO : put all errors that result in halting here

/*
 * Status codes 0-5 are reserved for execution control, such as normal state, stopped state etc.
 * Status codes 6-64 are reserved for general errors
 * Other status codes are command specific
 */

// No error
#define ERA_STATUS_NONE 0
// Normal exit caused by STOP
#define ERA_STATUS_STOP 1

// Command errors
#define ERA_STATUS_WRONG_REGISTER 6
#define ERA_STATUS_WRONG_FORMAT 7

// File errors
#define ERA_STATUS_FILE_ERROR 65
#define ERA_STATUS_FILE_VERSION_ERROR 66
#define ERA_STATUS_FILE_READ_ERROR 67

// Operator errors
#define ERA_STATUS_WRONG_OPERATOR 68

// Memory errors
#define ERA_STATUS_MEMORY_OUT_OF_BOUNDS 69

#endif //ERA_STATUS_H
