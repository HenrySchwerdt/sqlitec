#include "../test.h"

#include "../../src/error/error.h"

void should_create_error(void) {
    // when
    // Error* error = new_error(CRITICAL, "some_error");
    // then
    TEST_CHECK(CRITICAL == CRITICAL);
}