# pragma once
#ifndef DEBUGMODE
#include <iostream>
#  define DEBUG_LOG(x) do {std::cerr << x;} while (0)
#  define FLUSH() do {std::cerr.flush();} while (0)
#else
#  define DEBUG_LOG(x) do {} while (0)
#endif


#include <raylib.h>

struct vec2 : public Vector2 {
    vec2(float _x, float _y){
        x = _x;
        y = _y;
    }
};

/**
 * @brief ivec2: 2D Integer vector (good for xy coordinates).
 * 
 */

struct ivec2_ {
    ivec2_(int x, int y):x(x),y(y){}
    ivec2_(Vector2 floatvec) {
        x = floatvec.x;
        y = floatvec.y;
    }
    int x = 0, y = 0;
};
typedef struct ivec2_ ivec2;

/**
 * @brief Base class for all components.
 * 
 * For now, mostly just for distinguishing between component structs 
 * and non-component structs.
 */
struct Component {
    virtual ~Component() {}
};