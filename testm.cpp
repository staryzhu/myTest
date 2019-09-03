#include <stdio.h>

#define MEMORY_FENCE         __asm__ __volatile__ ("mfence"   : : : "memory")
#define MEMORY_FENCE_ACQUIRE __asm__ __volatile__ (""         : : : "memory")
//same as __sync_synchronize()


#include <stdlib.h>     /* exit */
#include <setjmp.h>     /* jmp_buf, setjmp, longjmp */

#include "mymath.h"

struct X {
  X() { fprintf(stderr, "X::ctor\n"); }
  ~X() { fprintf(stderr, "X::dtor\n"); }
};

void secondStack(int a, int b) {
    int c = 0x3333;
    int d = 0x4444;
}

void firstStack(int a, int b) {
    int c = 0x1111;
    int d = 0x2222;
    secondStack(a + 0x1111, b + 0x1111);
}
#define TEST_STACK
int main() {
#ifdef TEST_STACK
    int a = 0xaaaa;
    int b = 0xcccc;
    firstStack(a + 0x1111, b + 0x1111);
    my_add(a, b);
#else
    jmp_buf env;
    int val = -1;
    int m = -3;
    volatile int n = -2;
    X x;
    int *p = &val;
    val = setjmp(env);
    fprintf(stderr, "setjmp return: %d\n", val);
    if (val) {
        fprintf(stderr, "m: %d\n", m);
        //printf("&m: %x, m: %d\n", &m, *((int *)&m));
        fprintf(stderr, "n: %d\n", n);
        exit(val);
    }
    else {
        m = 2018;
        n = 2019;
        //printf("&m: %x, m: %d\n", p, *(--p));
        // printf("&m: %x, m: %d\n", p, *(++p));
        // printf("&m: %x, m: %d\n", p, *(++p));
        // printf("&m: %x, m: %d\n", p, *(++p));
        /* code here */
        longjmp(env, 19);   /* signaling an error */
        return 0;
    }

#endif

    return 0;

}
