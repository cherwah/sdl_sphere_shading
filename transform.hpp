#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "structs.hpp"


// bring model from object space to world space
void to_world_space(std::vector<vec3>& model_vrtx, world_attr& world_attr, std::vector<vec3>& world_vrtx) 
{
    for (int i=0; i<model_vrtx.size(); i++) {
        vec3 v = model_vrtx[i] * world_attr.scale;
        // v = v * world_attr.rot;
        v = v + world_attr.trans;
        world_vrtx.emplace_back(v);
    }
};

// determine camera space axis vectors and camera's origin-offset
void setup_cam_attr(cam_attr& cam_attr, vec3& pos, vec3& up, vec3& look) 
{
    cam_attr.pos = pos;
    cam_attr.look = look;
    cam_attr.up = up;

    // normalize axis vectors
    cam_attr.up.norm();
    cam_attr.look.norm();
    
    // using left-hand rule (where the thumb points in the direction of the cross product)
    cam_attr.right = cam_attr.up.cross(cam_attr.look);
    cam_attr.right.norm();

    // re-compute 'up' vector to ensure orthogonality.
    // no need to do it for cam_attr.look because that's our reference vector.
    cam_attr.up = cam_attr.look.cross(cam_attr.right);

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
        v.x = world_vrtx[i].x * cam_attr.right.x 
            + world_vrtx[i].y * cam_attr.right.y 
            + world_vrtx[i].z * cam_attr.right.z 
            + cam_attr.orig_ofst.x;

        // align to new y-axis
        v.y = world_vrtx[i].x * cam_attr.up.x
            + world_vrtx[i].y * cam_attr.up.y
            + world_vrtx[i].z * cam_attr.up.z
            + cam_attr.orig_ofst.y;

        // align to new z-axis
        v.z = world_vrtx[i].x * cam_attr.look.x
            + world_vrtx[i].y * cam_attr.look.y
            + world_vrtx[i].z * cam_attr.look.z
            + cam_attr.orig_ofst.z;

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

    float eps = 0.0001;

    for (int i=0; i<cam_vrtx.size(); i++) {
        vec3 v;

        float z = proj_attr.near / (cam_vrtx[i].z + eps);

        v.x = cam_vrtx[i].x * z;
        v.y = cam_vrtx[i].y * z;

        // v.x = cam_vrtx[i].x * fov_y * aspect * z;
        // v.y = cam_vrtx[i].y * fov_y * z;
        v.z = cam_vrtx[i].z;

        srn_vrtx.emplace_back(v);
    }
}

void to_srn_space(std::vector<vec3>& proj_vrtx, proj_attr& proj_attr, std::vector<vec3>& srn_vrtx) 
{
    float half_wd = proj_attr.width / 2;
    float half_ht = proj_attr.height / 2;

    for (int i=0; i<proj_vrtx.size(); i++) {
        vec3 v;

        // v.x = proj_vrtx[i].x + half_wd;
        // v.y = proj_vrtx[i].y + half_ht; 

        v.x = proj_vrtx[i].x * half_wd + half_wd;
        v.y = proj_vrtx[i].y * -half_ht + half_ht; 
        v.z = proj_vrtx[i].z;

        srn_vrtx.emplace_back(v);
    }
}


#endif