#ifndef MODEL_HPP
#define MODEL_HPP

#include "structs.hpp"
#include <iostream>
#include <cmath>

void create_uv_sphere(std::vector<vector3d>& vertices) {
    float r = 5.0;

    for (float i=0; i<20; i++) {
        float u = 2.0 * M_PI / 20.0;
        for (int j=0; j<20; j++) {
            float v = M_PI / 20.0;
            float x = r * cos(u) * sin(v);
            float y = r * sin(u) * sin(v);
            float z = r * cos(v);

            vertices.emplace_back(vector3d(x, y, z));
        }
    }
}

#endif