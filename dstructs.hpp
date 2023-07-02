#ifndef DSTRUCT_HPP
#define DSTRUCT_HPP


class vector3d {
public:
    vector3d() : x(0), y(0), z(0) {};
    vector3d(float x, float y, float z) : x(x), y(y), z(0) {};

    float x, y, z;
};

class rgba {
public:
    rgba() : r(0), g(0), b(0), a(0) {}; 
    rgba(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};

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