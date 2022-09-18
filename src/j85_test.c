#include "j85_test.h"

#include "j85_assert.h"

void run_test_case(j85_test_case_t* tc) { tc->test_fn(&tc->test); }

void __j85_assert_true(bool x) { j85_assert(x); }
