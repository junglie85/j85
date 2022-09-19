#include "j85_test.h"

#include "j85_assert.h"

#include <stdio.h>
#include <string.h>

void j85_log_fn(const char* msg) { fprintf(stdout, ""); }

void j85_test_set_log_file(j85_test_case_t* tc, FILE* f) { tc->log_file = f; }

void j85_test_run_test_case(j85_test_case_t* tc)
{
    if (tc->setup_fn) {
        tc->setup_fn(tc->data);
    }

    if (tc->test_fn) {
        tc->test_fn(tc->data);
        fprintf(tc->log_file, "[ PASS ] --- %s\n", tc->name);
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
