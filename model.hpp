#ifndef MODEL_HPP
#define MODEL_HPP

#include "structs.hpp"
#include <iostream>
#include <cmath>

/*
A UV sphere is defined using spherical coordinates (r, θ, φ), 
where r is the radius, θ is the azimuthal angle, and φ is the 
polar angle. The U parameter typically corresponds to θ and 
sweeps around the equator of the sphere, while the V parameter 
corresponds to φ and goes from the south pole to the north pole. 
For each pair of (U, V) values, we calculate a corresponding 
point on the surface of the sphere in 3D space using the formulas:

x = r * sin(φ) * cos(θ)
y = r * sin(φ) * sin(θ)
z = r * cos(φ)
*/
void uv_sphere(std::vector<vec3>& vrtx) 
{
    float r = 5.0;

    for (float i=0; i<20; i++) {
        float u = 2.0 * M_PI / 20.0;
        for (int j=0; j<20; j++) {
            float v = M_PI / 20.0;
            float x = r * cos(u) * sin(v);
            float y = r * sin(u) * sin(v);
            float z = r * cos(v);

            vrtx.emplace_back(vec3(x, y, z));
        }
    }
}

void rect(std::vector<vec3>& vrtx) 
{
    vrtx.emplace_back(vec3(-5.0, -5.0, 0.0));
    vrtx.emplace_back(vec3(5.0, -5.0, 0.0));
    vrtx.emplace_back(vec3(5.0, 5.0, 0.0));
    vrtx.emplace_back(vec3(-5.0, 5.0, 0.0));
}

#endif