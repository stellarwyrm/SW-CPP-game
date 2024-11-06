# pragma once
#ifndef DEBUGMODE
#include <iostream>
#  define DEBUG_LOG(x) do {std::cerr << x;} while (0)
#else
#  define DEBUG_LOG(x) do {} while (0)
#endif

struct ivec2_ {
    ivec2_(int x_, int y_):x(x_),y(y_){}
    int x, y;
};
typedef struct ivec2_ ivec2;
