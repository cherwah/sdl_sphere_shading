#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "dstructs.hpp"


// bring model from object space to world space
void to_world_space(std::vector<vector3d>& model_vertices, world_info& world_info, std::vector<vector3d>& world_vertices) {
    for (int i=0; i<model_vertices.size(); i++) {
        vector3d v = model_vertices[i] * world_info.scale;
        v = v * world_info.rotate;
        v = v + world_info.translate;
        world_vertices.emplace_back(v);
    }
};

// bring model to camera space
void to_camera_space(std::vector<vector3d>& world_vertices, cam_info& cam_info, std::vector<vector3d>& cam_vertices) {
    cam_info.up.normalize();
    cam_info.look.normalize();
    
    // using right-hand rule (where the thumb points in the direction of the cross product),
    // so the first vector is the index finger (look) and the second vector is the middle finger (up).
    cam_info.right = cam_info.look.cross_product(cam_info.up);
    cam_info.right.normalize();

    // re-compute 'up' vector to ensure orthogonality.
    // no need to do it for cam_info.look because that's our reference vector.
    cam_info.up = cam_info.right.cross_product(cam_info.look);

}

// projecting 3d vertices to 2d vertices
void to_projection_space(std::vector<vector3d>& vertices, proj_info& proj_info, std::vector<vector3d>& proj_vertices) {
}

// perspective division and clip vertices within frustum volume
void to_clip_space(std::vector<vector3d>& vertices, std::vector<vector3d>& clip_vertices) {
}

// maps NDC values to a SDL graphics window
void to_screen_space(std::vector<vector3d>& clip_vertices, std::vector<vector3d>& srn_vertices) {
}   

#endif