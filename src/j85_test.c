#include "j85_test.h"

#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static jmp_buf jmp_ctx;

j85_test_case_t j85_test_create_test(
    const char* name, void (*test_fn)(void*), void (*setup_fn)(void*), void (*teardown_fn)(void*), void* data)
{
    j85_test_case_t tc = {
        .name = name,
        .test_fn = test_fn,
        .setup_fn = setup_fn,
        .teardown_fn = teardown_fn,
        .out_buf_ptr = NULL,
        .data = data,
    };

    return tc;
}

void j85_test_set_out_buf_ptr(j85_test_case_t* tc, char** ptr) { tc->out_buf_ptr = ptr; }

static void signal_handler(int sig)
{
    if (sig != SIGABRT) {
        raise(sig);
    }
    longjmp(jmp_ctx, 1);
}

void j85_test_run_test_case(j85_test_case_t* tc)
{
    if (tc->setup_fn) {
        tc->setup_fn(tc->data);
    }

    if (tc->test_fn) {
        sig_t old_sigabrt = signal(SIGABRT, signal_handler);
        if (old_sigabrt == SIG_ERR) {
            abort();
        }

        bool test_pass = false;
        if (setjmp(jmp_ctx) == 0) {
            tc->test_fn(tc->data);
            test_pass = true;
        }

        signal(SIGABRT, old_sigabrt);

        size_t size = 0;
        FILE* out = tc->out_buf_ptr ? open_memstream(tc->out_buf_ptr, &size) : stdout;
        fprintf(out, "[ %s ] --- %s\n", test_pass ? "PASS" : "FAIL", tc->name);
        if (tc->out_buf_ptr) {
            fclose(out);
        }
    }

    if (tc->teardown_fn) {
        tc->teardown_fn(tc->data);
    }
}

static void fail() { abort(); }

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
