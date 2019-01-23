#ifndef ERRIC_STATUS_H
#define ERRIC_STATUS_H

/*
 * Status codes 0-5 are reserved for execution control, such as normal state, stopped state etc.
 * Status codes 6-64 are reserved for general errors
 * Other status codes are command specific
 */

// No error
#define ERRIC_STATUS_NONE 0
// Normal exit caused by STOP
#define ERRIC_STATUS_STOP 1

// Generic instruction errors
#define ERRIC_STATUS_WRONG_REGISTER 6
#define ERRIC_STATUS_WRONG_FORMAT 7

// File errors
#define ERRIC_STATUS_FILE_ERROR 65
#define ERRIC_STATUS_FILE_VERSION_ERROR 66
#define ERRIC_STATUS_FILE_READ_ERROR 67

// Operator errors
#define ERRIC_STATUS_WRONG_OPERATOR 68

// Memory errors
#define ERRIC_STATUS_MEMORY_OUT_OF_BOUNDS 69

#endif //ERRIC_STATUS_H
