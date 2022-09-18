#pragma once

#include "j85_api_types.h"

typedef struct j85_test_t {
    bool was_run;
} j85_test_t;

typedef struct j85_test_case_t {
    j85_test_t test;
    void (*test_fn)(j85_test_t*);
} j85_test_case_t;

void run_test_case(j85_test_case_t* tc);

#define j85_test_case(fn)                                                                         \
    {                                                                                             \
        {}, (fn)                                                                                  \
    }

void __j85_assert_true(bool x);
#define j85_assert_true(x) __j85_assert_true((x))
#define j85_assert_false(x) __j85_assert_true(!(x))
