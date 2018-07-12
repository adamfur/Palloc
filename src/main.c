#include <signal.h>
#include <setjmp.h>
#include "palloc.h"
#include <assert.h>

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char bool;

bool segfault;
jmp_buf escape;

void captureSegfault(int signum);
void test(const char *function, int size, int element, bool expectSegfault, void *(*alloc)(size_t));

int main(int argc, char *argv[])
{
    void *x = palloc(4);
    pfree(x);
    return 1;
    test("malloc", 23, 22, FALSE, malloc);
    test("malloc", 23, 23, FALSE, malloc);
    test("palloc", 23, 22, FALSE, __palloc);
    test("palloc", 23, 23, TRUE, __palloc);
    test("palloc", 10000, 9999, FALSE, __palloc);
    test("palloc", 10000, 10000, TRUE, __palloc);
    return 0;
}

void test(const char *function, int size, int element, bool expectSegfault, void *(*alloc)(size_t))
{
    signal(SIGSEGV, captureSegfault);
    char *memory = (char *)(*alloc)(size);

    segfault = FALSE;
    if (!setjmp(escape))
    {
        for (int i = 0; i <= element; ++i)
        {
            *(memory + i) = 0;
        }
    }

    assert(segfault == expectSegfault);
    printf("%s(%d) segfault: %s\n", function, size, (segfault ? "true" : "false"));
}

void captureSegfault(int signum)
{
    sigset_t block_sigint, prev_mask;
    sigemptyset(&block_sigint);

    if (sigprocmask(SIG_SETMASK, &block_sigint, &prev_mask) < 0)
    {
        perror("Couldn't block SIGSEGV");
        return;
    }
    segfault = TRUE;
    longjmp(escape, 1);
}
