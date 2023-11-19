#ifndef error_h
#define error_h

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

#endif