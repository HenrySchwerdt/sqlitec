#include <ctest.h>

#include "../../src/error/error.h"

CTEST(error, new_error) {
    Error* error = new_error(CRITICAL, "some_error");
    ASSERT_EQUAL(CRITICAL, error->type);
}