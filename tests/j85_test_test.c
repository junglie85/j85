#include "j85_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    j85_test_run_test_case(&tc);

    j85_assert_str_eq(user_data.msg, "setup;test_method;teardown;");
}

void test_case_logging_passing_test(void* data)
{
    char* buf;

    user_data_t user_data = {};
    j85_test_case_t tc = j85_test_case_setup_teardown_user_data(
        test_system_under_test, test_system_under_test_setup, NULL, &user_data);
    j85_test_set_out_buf_ptr(&tc, &buf);

    j85_test_run_test_case(&tc);

    j85_assert_str_eq(buf, "[ PASS ] --- test_system_under_test\n");
}

void test_case_logging_failing_test(void* data)
{
    char* buf;

    user_data_t user_data = {};
    j85_test_case_t tc
        = j85_test_case_setup_teardown_user_data(test_system_under_test, NULL, NULL, &user_data);
    j85_test_set_out_buf_ptr(&tc, &buf);

    j85_test_run_test_case(&tc);

    j85_assert_str_eq(buf, "[ FAIL ] --- test_system_under_test\n");
    // TODO: Failure reason ...
}

void test_fails(void* data) { j85_assert_true(false); }

int main(void)
{
    j85_test_case_t tc = j85_test_case(test_assert_true);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_false);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_strings_equal);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_assert_strings_not_equal);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_case_test);
    j85_test_run_test_case(&tc);

    user_data_t user_data = {};
    tc = (j85_test_case_t)j85_test_case_setup_teardown_user_data(test_system_under_test,
        test_system_under_test_setup, test_system_under_test_teardown, &user_data);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_case_logging_passing_test);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_case_logging_failing_test);
    j85_test_run_test_case(&tc);

    tc = (j85_test_case_t)j85_test_case(test_fails);
    j85_test_run_test_case(&tc);

    // TODO: Non-zero exit code for test failure?
}
