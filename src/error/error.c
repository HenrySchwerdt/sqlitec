#include "error.h"

Error* new_error(ErrorType type, char* message) {
    Error* error = (Error*)malloc(sizeof(Error));
    if (error != NULL) {
        error->type = type;
        error->message = message;
    }
    return error;
}

void free_error(Error* error) {
    if (error != NULL) {
        free(error->message);
        free(error);
    }
}