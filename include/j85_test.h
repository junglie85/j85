#pragma once

#include "j85_api_types.h"

#define j85_test_case(fn)                                                                         \
    {                                                                                             \
        (#fn), (fn), NULL, NULL, NULL, NULL                                                       \
    }

#define j85_test_case_user_data(fn, data)                                                         \
    {                                                                                             \
        (#fn), (fn), NULL, NULL, NULL, (data)                                                     \
    }

#define j85_test_case_setup_teardown_user_data(fn, setup, teardown, data)                         \
    {                                                                                             \
        (#fn), (fn), (setup), (teardown), NULL, (data)                                            \
    }

typedef struct j85_test_case {
    const char* name;
    void (*test_fn)(void*);
    void (*setup_fn)(void*);
    void (*teardown_fn)(void*);
    char** out_buf_ptr;
    void* data;
} j85_test_case_t;

void j85_test_set_out_buf_ptr(j85_test_case_t* tc, char** ptr);

void j85_test_run_test_case(j85_test_case_t* tc);

void __j85_assert_true(bool x);
#define j85_assert_true(x) __j85_assert_true((x))
#define j85_assert_false(x) __j85_assert_true(!(x))

void __j85_assert_str_eq(const char* a, const char* b);
#define j85_assert_str_eq(a, b) __j85_assert_str_eq((a), (b))

void __j85_assert_str_ne(const char* a, const char* b);
#define j85_assert_str_ne(a, b) __j85_assert_str_ne((a), (b))
