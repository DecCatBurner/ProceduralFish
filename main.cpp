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

    Vec4 chainColor = Vec4(0, 255, 255);

    Chain b = Chain();
    for (int i = 0; i < 3; i++){
        b.segments[i] = Ball();
    }
    //Segment a, c, d;
    //b.AddSegment(&a);
    //b.AddSegment(&c);
    //b.AddSegment(&d);

    while (true) {
        SDL_Delay(1);
        //iTime = SDL_GetTicks64() * 0.001f;

        SDL_SetRenderDrawColor(rend, 0, 60, 180, 255);
        SDL_RenderClear(rend);

        /*
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        Draw::Circle(rend, Vec2(HALF_WIDTH, HALF_HEIGHT), 100);
        */
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        Vec2<int> mouse(mx, my);
        b.Move(Vec::Normalize(mouse - b.pos));
        b.Draw(rend);

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