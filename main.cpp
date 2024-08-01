#include <iostream>
#include "obj.cpp"

//const int WIDTH = 800, HEIGHT = 600; this is declared in draw for simplicity

int main(int argsc, char *argsv[]) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow("Procedural Fish \u00A9DecCatBurner 2024", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, 1);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    //float iTime = SDL_GetTicks();

    Ball b = Ball(40, Vec2(HALF_WIDTH, HALF_HEIGHT), Vec2(20, 20), Vec4(0, 255, 255, 255));

    while (true) {
        SDL_Delay(1);
        //iTime = SDL_GetTicks64() * 0.001f;

        SDL_SetRenderDrawColor(rend, 0, 60, 180, 255);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        Draw::Circle(rend, Vec2(HALF_WIDTH, HALF_HEIGHT), 100);

        int mx, my;
        SDL_GetMouseState(&mx, &my);
        Vec2<int> mouse(mx, my);
        //int l = Vec::Length(mouse);
        /*if (l > 60) {
            mouse = Vec2(mouse.x / l, mouse.y / l);
            mouse = Vec2(mouse.x * 60, mouse.y * 60);
        }*/
        b.SetPos(mouse + Vec2<int>::one * 10);
        b.Draw(rend);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        Draw::CircleOutline(rend, Vec2(HALF_WIDTH, HALF_HEIGHT), 100, 10);

        SDL_RenderPresent(rend);
        if ( SDL_PollEvent( &windowEvent ) ) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
    }

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( rend );
    SDL_Quit();

    return EXIT_SUCCESS;
} // mingw32-make