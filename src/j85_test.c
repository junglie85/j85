#include "j85_test.h"

#include "j85_assert.h"

#include <stdio.h>
#include <string.h>

void j85_test_set_out_buf_ptr(j85_test_case_t* tc, char** ptr) { tc->out_buf_ptr = ptr; }

void j85_test_run_test_case(j85_test_case_t* tc)
{
    if (tc->setup_fn) {
        tc->setup_fn(tc->data);
    }

    if (tc->test_fn) {
        tc->test_fn(tc->data);

        size_t size = 0;
        FILE* out = tc->out_buf_ptr ? open_memstream(tc->out_buf_ptr, &size) : stdout;
        fprintf(out, "[ PASS ] --- %s\n", tc->name);
        if (tc->out_buf_ptr) {
            fclose(out);
        }
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
