#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "structs.hpp"


void draw_text(SDL_Surface* surface, TTF_Font* font, int x, int y, std::string text, std::string h_align="left") {
    uint margin = 10;

    // using black as the transparent color
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));

    // white text
    SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font, text.c_str(), { 255, 255, 255, 255 });

    SDL_Rect rect;
    TTF_SizeText(font, text.c_str(), &rect.w, &rect.h);

    // text alignment
    y += margin;
    if (h_align == "left") {
        x += margin;
    } else if (h_align == "right") {
        x = surface->w - rect.w - margin;
    } else if (h_align == "center") {
        x = (surface->w - rect.w)/2 - rect.w/2;
    }

    // blit text surface to the main surface
    SDL_BlitSurface(text_surface, NULL, surface, new SDL_Rect{ x, y, rect.w, rect.h });

    SDL_FreeSurface(text_surface);
}

