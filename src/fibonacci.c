//
// Created by efreyu on 11.04.2020.
//
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int fib(int n) {
    int i, t, a = 0, b = 1;
    for (i = 0; i < n; i++) {
        t = a + b;
        a = b;
        b = t;
    }
    return b;
}
