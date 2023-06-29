#ifndef DSTRUCT_HPP
#define DSTRUCT_HPP


class point2d {
public:
    point2d() : x(0), y(0) {};
    point2d(float x, float y) : x(x), y(y) {};

    float x, y;
};


class point3d {
public:
    point3d() : x(0), y(0), z(0) {};
    point3d(float x, float y, float z) : x(x), y(y), z(z) {};

    float x, y, z;
};


class rgba {
public:
    rgba() : r(0), g(0), b(0), a(0) {}; 
    rgba(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};

    int r, g, b, a;
};


class vertex2d {
public:
    vertex2d(point2d pos, rgba color) : pos(pos), color(color) {}

    point2d pos;
    rgba color;
};


class vertex3d {
public:
    vertex3d(point3d pos, rgba color) : pos(pos), color(color) {}

    point3d pos;
    rgba color;
};


class edge2d {
public:
    edge2d(vertex2d v0, vertex2d v1) : v0(v0), v1(v1) {}

    vertex2d v0, v1;
};


class edge3d {
public:
    edge3d(vertex3d v0, vertex3d v1) : v0(v0), v1(v1) {}

    vertex3d v0, v1;
};


#endif