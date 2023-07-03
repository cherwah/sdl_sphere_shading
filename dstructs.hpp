#ifndef DSTRUCT_HPP
#define DSTRUCT_HPP

#include <cmath>

class point2d {
public:
    point2d(int x=0, int y=0) : x(x), y(y) {};

    int x, y;
};

class vector3d {
public:
    vector3d(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {};

    vector3d operator+(const vector3d& rhs) {
        return vector3d(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    vector3d operator*(const vector3d& rhs) {
        return vector3d(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    float dot_product(const vector3d& rhs) {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    vector3d cross_product(const vector3d& rhs) {
        return vector3d(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    void normalize() {
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

class vertex3d {
public:
    vertex3d(vector3d& pos, rgba& color) 
        : pos(pos), color(color) {}

    vector3d pos;
    rgba color;
};

class edge3d {
public:
    edge3d(vertex3d& v0, vertex3d& v1) 
        : v0(v0), v1(v1) {}

    vertex3d v0, v1;
};

class world_info {
public:
    world_info(vector3d& scale, vector3d& rotate, vector3d& translate) 
        : scale(scale), rotate(rotate), translate(translate) {}

    vector3d scale, rotate, translate;
};

class cam_info {
public:
    cam_info(vector3d& pos, vector3d& up, vector3d& look)
        : pos(pos), up(up), look(look) {}

    vector3d pos, up, look;
};

class proj_info {
public:
    proj_info(float fov, float aspect_ratio, float near, float far)
        : fov(fov), aspect_ratio(aspect_ratio), near(near), far(far) {}

    float fov, aspect_ratio, near, far;
};




#endif