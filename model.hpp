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
void uv_sphere(std::vector<vec3>& vrtx, float r, int n_stacks, int n_slices) 
{
    for (int i=0; i<n_stacks - 1; i++) {
        float phi = (i + 1) * M_PI / n_stacks;
     
        for (int j=0; j<n_slices; j++) {
            float theta = j * 2 * M_PI / n_slices;
     
            float x = r * sin(phi) * cos(theta);
            float y = r * cos(phi);
            float z = r * sin(phi) * sin(theta);
     
            vrtx.emplace_back(vec3(x, y, z));
        }
    }
}

void rect(std::vector<vec3>& vrtx) 
{
    vrtx.emplace_back(vec3(-0.5, -0.5, 5.0));
    vrtx.emplace_back(vec3(0.5, -0.5, 5.0));
    vrtx.emplace_back(vec3(0.5, 0.5, 5.0));
    vrtx.emplace_back(vec3(-0.5, 0.5, 5.0));
}

#endif