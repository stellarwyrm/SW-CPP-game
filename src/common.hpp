# pragma once
#ifndef DEBUGMODE
#include <iostream>
#  define DEBUG_LOG(x) do {std::cerr << x;} while (0)
#  define FLUSH() do {std::cerr.flush();} while (0)
#else
#  define DEBUG_LOG(x) do {} while (0)
#endif

/**
 * @brief ivec2: 2D Integer vector (good for xy coordinates).
 * 
 */

struct ivec2_ {
    ivec2_(int x_, int y_):x(x_),y(y_){}
    int x, y;
};
typedef struct ivec2_ ivec2;

/**
 * @brief Base class for all components.
 * 
 * For now, mostly just for distinguishing between component structs 
 * and non-component structs.
 */
struct Component {
    virtual ~Component();
};