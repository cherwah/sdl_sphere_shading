#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void draw_text(SDL_Surface*, TTF_Font*, int, int, std::string, std::string="left");

#endif