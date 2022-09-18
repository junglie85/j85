#pragma once

#include "j85_api_types.h"

#define j85_test_case(fn)                                                                         \
    {                                                                                             \
        (fn), NULL, NULL, NULL                                                                    \
    }

#define j85_test_case_user_data(fn, data)                                                         \
    {                                                                                             \
        (fn), NULL, NULL, (data)                                                                  \
    }

#define j85_test_case_setup_teardown_user_data(fn, setup, teardown, data)                         \
    {                                                                                             \
        (fn), (setup), (teardown), (data)                                                         \
    }

typedef struct j85_test_case {
    void (*test_fn)(void*);
    void (*setup_fn)(void*);
    void (*teardown_fn)(void*);
    void* data;
} j85_test_case_t;

void run_test_case(j85_test_case_t* tc);

void __j85_assert_true(bool x);
#define j85_assert_true(x) __j85_assert_true((x))
#define j85_assert_false(x) __j85_assert_true(!(x))

void __j85_assert_str_eq(const char* a, const char* b);
#define j85_assert_str_eq(a, b) __j85_assert_str_eq((a), (b))

void __j85_assert_str_ne(const char* a, const char* b);
#define j85_assert_str_ne(a, b) __j85_assert_str_ne((a), (b))
