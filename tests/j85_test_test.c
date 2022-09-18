#include "j85_test.h"

void was_run(j85_test_t* t) { t->was_run = true; }

void test_was_run(j85_test_t* t)
{
    j85_assert_false(t->was_run);
    was_run(t);
    j85_assert_true(t->was_run);
}

int main(void)
{
    j85_test_case_t tc = j85_test_case(test_was_run);
    run_test_case(&tc);
}
