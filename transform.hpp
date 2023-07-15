#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "structs.hpp"



// bring model from object space to world space
void to_world_space(std::vector<vec3>& model_vrtx, world_attr& world_attr, std::vector<vec3>& world_vrtx) 
{
    for (int i=0; i<model_vrtx.size(); i++) {
        vec3 v = model_vrtx[i] * world_attr.scale;
        v = v * world_attr.rot;
        v = v + world_attr.trans;
        world_vrtx.emplace_back(v);
    }
};

// determine camera space axis vectors and camera's origin-offset
void setup_cam_attr(cam_attr& cam_attr, vec3& pos, vec3& look, vec3& up) 
{
    cam_attr.pos = pos;
    cam_attr.look = look;
    cam_attr.up = up;

    // normalize axis vectors
    cam_attr.up.norm();
    cam_attr.look.norm();
    
    // using right-hand rule (where the thumb points in the direction of the cross product),
    // so the first vector is the index finger (look) and the second vector is the middle finger (up).
    cam_attr.right = cam_attr.look.cross(cam_attr.up);
    cam_attr.right.norm();

    // re-compute 'up' vector to ensure orthogonality.
    // no need to do it for cam_attr.look because that's our reference vector.
    cam_attr.up = cam_attr.right.cross(cam_attr.look);

    // compute origin-offset (so that models can be viewed from the camera's 
    // perspective after adding the origin-offset; where the camera is at 
    // the origin of the camera space).
    // note: the camera need not be at the origin of the world space.
    cam_attr.orig_ofst.x = -cam_attr.right.dot(cam_attr.pos);
    cam_attr.orig_ofst.y = -cam_attr.up.dot(cam_attr.pos);
    cam_attr.orig_ofst.z = -cam_attr.look.dot(cam_attr.pos);
}

// bring model to camera space coordinates
void to_cam_space(std::vector<vec3>& world_vrtx, cam_attr& cam_attr, std::vector<vec3>& cam_vrtx) 
{
    for (int i=0; i<world_vrtx.size(); i++) {
        vec3 v;

        // align to new x-axis
        v.x = world_vrtx[i].x * cam_attr.right.x;
        v.y = world_vrtx[i].y * cam_attr.right.y;
        v.z = world_vrtx[i].z * cam_attr.right.z;

        // align to new y-axis
        v.x *= cam_attr.up.x;
        v.y *= cam_attr.up.y;
        v.z *= cam_attr.up.z;

        // align to new z-axis
        v.x *= cam_attr.look.x;
        v.y *= cam_attr.look.y;
        v.z *= cam_attr.look.z;

        // move to the front of the camera
        v.x += cam_attr.orig_ofst.x;
        v.y += cam_attr.orig_ofst.y;
        v.z += cam_attr.orig_ofst.z;

        cam_vrtx.emplace_back(v);
    }
}

// projecting 3d vrtx to 2d vrtx
// x' = x * f * AR * (z_n / z)
// y' = y * f * (z_n / z)
void to_proj_space(std::vector<vec3>& cam_vrtx, proj_attr& proj_attr, std::vector<vec3>& srn_vrtx) 
{
    float aspect = proj_attr.width / proj_attr.height;
    float fov_y = 1 / tan(proj_attr.fov_y_rad / 2);

    for (int i=0; i<cam_vrtx.size(); i++) {
        vec3 v;

        // normalize x and y with z;
        if (cam_vrtx[i].z == 0) {
            v.x = cam_vrtx[i].x;
            v.y = cam_vrtx[i].y;
        } else {
            v.x = cam_vrtx[i].x / cam_vrtx[i].z;
            v.y = cam_vrtx[i].y / cam_vrtx[i].z;
        }
        v.z = cam_vrtx[i].z;

        // taking aspect ratio of screen for projection into consideration
        v.x *= fov_y * aspect * (proj_attr.near / v.z);
        v.y *= fov_y * (proj_attr.near / v.z);

        srn_vrtx.emplace_back(v);
    }
}


#endif