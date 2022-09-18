#include "j85_test.h"

#include "j85_assert.h"

#include <string.h>

void run_test_case(j85_test_case_t* tc)
{
    if (tc->setup_fn) {
        tc->setup_fn(tc->data);
    }

    if (tc->test_fn) {
        tc->test_fn(tc->data);
    }

    if (tc->teardown_fn) {
        tc->teardown_fn(tc->data);
    }
}

static void fail() { j85_assert(false); }

void __j85_assert_true(bool x)
{
    if (!x) {
        fail();
    }
}

void __j85_assert_str_eq(const char* a, const char* b)
{
    int rc = strcmp(a, b);
    if (rc != 0) {
        fail();
    }
}

void __j85_assert_str_ne(const char* a, const char* b)
{
    int rc = strcmp(a, b);
    if (rc == 0) {
        fail();
    }
}
