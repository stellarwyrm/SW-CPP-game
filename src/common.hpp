# pragma once
#ifndef DEBUGMODE
#include <iostream>
#  define DEBUG_LOG(x) do {std::cerr << x;} while (0)
#  define FLUSH() do {std::cerr.flush();} while (0)
#else
#  define DEBUG_LOG(x) do {} while (0)
#endif


#include <raylib.h>

// Coordinate systems
struct vec2;
struct ivec2;

struct coord2D {
    const vec2 getCoord();
};


struct vec2 : public Vector2, public virtual coord2D {
    vec2(float _x, float _y) {
        x = _x;
        y = _y;
    }
    vec2(ivec2 ivec);
    const vec2 getCoord() {
        return vec2(x, y);
    }
    vec2 operator+(vec2 const& vec) {
        return vec2(x + vec.x, y + vec.y);
    }
    vec2 operator*(vec2 const& vec) {
        return vec2(x * vec.x, y * vec.y);
    }
};


/**
 * @brief ivec2: 2D Integer vector (good for xy coordinates).
 * 
 */

struct ivec2: public virtual coord2D {
    ivec2(int x, int y):x(x),y(y){}
    ivec2(vec2 floatvec) {
        x = floatvec.x;
        y = floatvec.y;
    }
    ivec2 operator+(ivec2 const& vec) {
        return ivec2(x + vec.x, y + vec.y);
    }
    const vec2 getCoord() {
        return vec2(x,y);
    }
    int x = 0, y = 0;
};


/**
 * @brief polarVec2: polar coordinate vector (for spinning?)
 * 
 */
struct polarVec2: public virtual coord2D {
    polarVec2(float ang, float rad):angle(ang),radius(rad){}
    float angle;
    float radius;
    const vec2 getCoord () {
        return vec2(sin(angle) * radius, cos(angle) * radius);
    }
};

struct rgba : public Color {
    rgba(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0, unsigned char _a = 255)
    {
        r = _r; g = _g; b = _b; a = _a;
    }
    rgba(Color c)
    {
        r = c.r; g = c.g; b = c.b; a = c.a;
    }
};

/**
 * @brief Base class for all components.
 * 
 * For now, mostly just for distinguishing between component structs 
 * and non-component structs.
 */
struct Component {
    virtual ~Component() {}
};