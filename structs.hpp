#ifndef DSTRUCT_HPP
#define DSTRUCT_HPP

#include <cmath>

class point2d {
public:
    point2d(int x=0, int y=0) : x(x), y(y) {};

    int x, y;
};

class vec3 {
public:
    vec3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {};

    vec3 operator+(const vec3& rhs) {
        return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    vec3 operator*(const vec3& rhs) {
        return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    float dot(const vec3& rhs) {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    vec3 cross(const vec3& rhs) {
        return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    void norm() {
        float length = sqrt(x * x + y * y + z * z);
        
        x /= length;
        y /= length;
        z /= length;
    }

    float x, y, z;
};

class rgba {
public:
    rgba(int r=0, int g=0, int b=0, int a=0) : r(r), g(g), b(b), a(a) {};

    int r, g, b, a;
};

class vrtx3 {
public:
    vrtx3(vec3& pos, rgba& color) 
        : pos(pos), color(color) {}

    vec3 pos;
    rgba color;
};

class edge3d {
public:
    edge3d(vrtx3& v0, vrtx3& v1) 
        : v0(v0), v1(v1) {}

    vrtx3 v0, v1;
};

class world_attr {
public:
    world_attr(vec3& scale, vec3& rot, vec3& trans) 
        : scale(scale), rot(rot), trans(trans) {}

    vec3 scale, rot, trans;
};

class cam_attr {
public:
    cam_attr(vec3& pos, vec3& up, vec3& look)
        : pos(pos), up(up), look(look) {}

    vec3 pos, up, look, right, orig_ofst;
};

class proj_attr {
public:
    proj_attr(float fov_y_rad, float width, float height, float near, float far) 
        : fov_y_rad(fov_y_rad), width(width), height(height), near(near), far(far) {}

    float fov_y_rad, width, height, near, far;
};




#endif