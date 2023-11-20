#include "error.h"

Result* new_result(ResultType type, ResultData data) {
    Result* result = malloc(sizeof(Result));
    result->type = type;
    result->data.info = data.info;
    result->data.error = data.error;
    return result;
}

void free_result(Result* result) {
    if (result != NULL) {
        free(result);
    }
}