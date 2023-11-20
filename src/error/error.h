#ifndef error_h
#define error_h
#include <stdlib.h>
#include <string.h>

typedef enum {
    CRITICAL,
    ERROR,
    WARN,
} ErrorType;

typedef struct {
    ErrorType type;
    char* message;
} Error;

typedef struct {
    char* message;
} Info;

typedef enum {
    INFO,
    FAILURE
} ResultType;

typedef union {
    Error error;
    Info info;
} ResultData;

typedef struct {
    ResultType type;
    ResultData data;
   
} Result;

Result* new_result(ResultType type, ResultData data);

void free_result(Result* error);

#endif