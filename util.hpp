#ifndef UTIL_HPP
#define UTIL_HPP

#include <cmath>

float to_rad(float deg) {
    return deg * M_PI / 180.0;
}   

float to_deg(float rad) {
    return rad * 180.0 / M_PI;
}

#endif