#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "text.hpp"
#include "model.hpp"
#include "draw.hpp"
#include "transform.hpp"


int main(int argc, char* argv[]) 
{

    /******************************************************
     * Initialize SDL.
     *****************************************************/
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    TTF_Font* font;

    float width = 540;
    float height = 540;


    // initializing underlying grpahics API
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << "\n";
    }

    // create SDL window for graphics rendering
    if (!(window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))) {
        std::cout << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
    }

    // position window at bottom left of screen    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_SetWindowPosition(window, 0, DM.h - height);

    // get hardware renderer
    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << "\n"; 
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // create surface to draw on (intel and m1 chips use little endian; orders are flipped - that's why
    // red mask is 0x000000FF instead of 0xFF000000)
    surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

    // create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // init font
    if (TTF_Init() < 0) {
        std::cout << "TTF initialization failed: " << SDL_GetError() << "\n"; 
        SDL_Quit();
    }

    font = TTF_OpenFont("fonts/comic_code.ttf", 18);


    /******************************************************
     * Setup our Sphere model.
     *****************************************************/
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // create model
    std::vector<vec3> model_vrtx, world_vrtx, cam_vrtx, proj_vrtx, clip_vrtx, srn_vrtx;
    create_uv_sphere(model_vrtx);

    // transform to world space
    vec3 scale(1, 1, 1);
    vec3 rot(0, 0, 0);
    vec3 trans(0, 0, 0);
    world_attr world_attr(scale, rot, trans);
    to_world_space(model_vrtx, world_attr, world_vrtx);  

    // transform to camera space
    vec3 pos(0, 0, 0);
    vec3 up(0, 1, 0);
    vec3 look(0, 0, 1);
    cam_attr cam_attr(pos, up, look);
    to_cam_space(world_vrtx, cam_attr, cam_vrtx);
    


    /******************************************************
     * SDL Event Loop.
     *****************************************************/
    Uint32 times = 0, start_tick, fps = 60;

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
            }            
        }


        if (times == 0) {
            start_tick = SDL_GetTicks();
        }
        
        // clear screen
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 255));


        // draw model

        // std::vector
        // draw_uv_sphere(surface, model_vrtx);

        times++;
        draw_text(surface, font, 0, 0, "FPS: " + std::to_string(fps), "right");

        if (SDL_GetTicks() - start_tick >= 1000) {
            fps = times;
            times = 0;
        }      
        

        // update texture
        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);       
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // refresh graphics window
        SDL_RenderPresent(renderer);

        // close to 60 fps
        SDL_Delay(16);
    }

    /******************************************************
     * Clean up.
     *****************************************************/
    TTF_Quit();

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
