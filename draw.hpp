#ifndef DRAW_HPP
#define DRAW_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "dstructs.hpp"

void draw_uv_sphere(SDL_Surface* surface, std::vector<point2d>& vertices) 
{
    SDL_LockSurface(surface);

    Uint32 color = SDL_MapRGBA(surface->format, 255, 255, 255, 255);

    for (int i=0; i< vertices.size(); i++) {
        Uint32* pixel = (Uint32*)((Uint8*)surface->pixels + vertices[i].y * surface->pitch + vertices[i].x * surface->format->BytesPerPixel);
        *pixel = color;
    }

    SDL_UnlockSurface(surface);
}

#endif