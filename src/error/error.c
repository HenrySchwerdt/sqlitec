#include "error.h"

Error* new_error(ErrorType type, char* message) {
    Error error;
    error.type = type;
    error.message = message;
    return &error;
}