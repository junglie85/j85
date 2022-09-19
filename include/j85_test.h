#pragma once

#include "j85_api_types.h"

#define j85_test_case(fn) j85_test_create_test((#fn), (fn), NULL, NULL, NULL)
#define j85_test_case_state(fn, data) j85_test_create_test((#fn), (fn), NULL, NULL, (data))
#define j85_test_case_setup_teardown_state(fn, setup, teardown, data)                                                  \
    j85_test_create_test((#fn), (fn), (setup), (teardown), (data))

#define j85_assert_true(x) __j85_assert_true((x))
#define j85_assert_false(x) __j85_assert_true(!(x))
#define j85_assert_str_eq(a, b) __j85_assert_str_eq((a), (b))
#define j85_assert_str_ne(a, b) __j85_assert_str_ne((a), (b))

typedef struct j85_test_case {
    const char* name;
    void (*test_fn)(void*);
    void (*setup_fn)(void*);
    void (*teardown_fn)(void*);
    char** out_buf_ptr;
    void* data;
} j85_test_case_t;

j85_test_case_t j85_test_create_test(
    const char* name, void (*test_fn)(void*), void (*setup_fn)(void*), void (*teardown_fn)(void*), void* data);
void j85_test_set_out_buf_ptr(j85_test_case_t* tc, char** ptr);
void j85_test_run_test_case(j85_test_case_t* tc);

void __j85_assert_true(bool x);
void __j85_assert_str_eq(const char* a, const char* b);
void __j85_assert_str_ne(const char* a, const char* b);
