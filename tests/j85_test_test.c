#include "j85_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * when assert(fales), we get a SIGABRT. How catch this and record test failure?
 * catch SIGSEV and report it (e.g. when accessing bad pointer address)?
 */

typedef struct user_data {
    char msg[512];
} user_data_t;

void system_under_test(user_data_t* user_data) { strcat(user_data->msg, "test_method;"); }

void test_system_under_test(void* data)
{
    user_data_t* user_data = (user_data_t*)data;

    system_under_test(user_data);

    j85_assert_str_eq(user_data->msg, "setup;test_method;");
}

void test_assert_true(void* data) { j85_assert_true(true); }

void test_assert_false(void* data) { j85_assert_false(false); }

void test_assert_strings_equal(void* data) { j85_assert_str_eq("a string", "a string"); }

void test_assert_strings_not_equal(void* data) { j85_assert_str_ne("a string", "b string"); }

void test_system_under_test_setup(void* data)
{
    user_data_t* user_data = (user_data_t*)data;
    strcat(user_data->msg, "setup;");
}

void test_system_under_test_teardown(void* data)
{
    user_data_t* user_data = (user_data_t*)data;
    strcat(user_data->msg, "teardown;");
}

void test_case_test(void* data)
{
    user_data_t user_data = {};
    j85_test_case_t tc = j85_test_case_setup_teardown_user_data(test_system_under_test,
        test_system_under_test_setup, test_system_under_test_teardown, &user_data);

    run_test_case(&tc);

    j85_assert_str_eq(user_data.msg, "setup;test_method;teardown;");
}

int main(void)
{
    j85_test_case_t tc = j85_test_case(test_assert_true);
    run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_false);
    run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_strings_equal);
    run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_strings_not_equal);
    run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_case_test);
    run_test_case(&tc);

    user_data_t user_data = {};
    tc = (j85_test_case_t)j85_test_case_setup_teardown_user_data(test_system_under_test,
        test_system_under_test_setup, test_system_under_test_teardown, &user_data);
    run_test_case(&tc);
}
