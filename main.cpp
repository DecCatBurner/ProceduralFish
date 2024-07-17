#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argsc, char *argsv[]) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow("Procedural Fish \u00A9DecCatBurner 2024", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 1);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    int i = 0;
    int dir = 1;

    while (true) {
        if (i >= 100){
            dir = -1;
        } else if (i <= -100){
            dir = 1;
        }
        i+=dir;

        SDL_Delay(10);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, 600 + i, 500 + i, 200 + i, 100 + i);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, 600 + i, 100 - i, 200 + i, 500 - i);
        SDL_RenderPresent(renderer);
        if ( SDL_PollEvent( &windowEvent ) ) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
    }

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();

    return EXIT_SUCCESS;
} // mingw32-make