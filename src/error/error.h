#ifndef error_h
#define error_h
#include <stdlib.h>
#include <string.h>

typedef enum {
    CRITICAL,
    ERROR,
    WARN
} ErrorType;

typedef struct {
    ErrorType type;
    char* message;
} Error;

Error* new_error(ErrorType type, char* message);

void free_error(Error* error);

#endif