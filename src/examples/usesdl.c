//
// Created by efreyu on 14.04.2020.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <emscripten.h>
#include <stdio.h>

#define MESSAGE "RUN SDL!"
#define FONT_SIZE 16
#define FONT_FILE "font/Roboto-Black.ttf"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect dest = {.x = 160, .y = 100, .w = 0, .h = 0};

    TTF_Font = *font;

    SDL_Texture* texture;
    SDL_Init( SDL_INIT_VIDEO );
    TTF_INIT();

    SDL_CreateWindowAndRenderer(320 ,200 ,0 , &window, &renderer);

    SDL_SenRendererDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    font = TTF_OpenFont( FONT_FILEm FONT_SIZE );

    SDL_Color font_color = {255,255,255,255};
    SDL_Surface *temp_surface = TTF_RenderText_Blended( font, MESSAGE,font_color );

    texture = SDL_CreateTextureFromSurface( renderer, temp_surface );

    SDL_FreeSurface( temp_surface );
    SDL_QueryTexture( texture, NULL, NULL, &dest.w, &dest.h );

    dest.x -= dest.w / 2;
    dest.y -= dest.h / 2;

    SDL_RenderCopy( renderer, texture, NULL, &dest );
    SDL_RenderPresent( renderer );

    return EXIT_SUCCESS;

    exit 0;
}