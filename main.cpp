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
    // End init

    Color circleColor1 = Color(250, 100, 20, 255);
    Color circleColor2 = Color(200, 150, 30, 255);

    float circleSize = 25.0f;

    Ball tailSegments[50];
    for (int i = 0; i < sizeof(tailSegments)/sizeof(Ball); i++) {
        tailSegments[i] = Ball(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(50-i)/50.0f, (i%2 == 1) ? circleColor1 : circleColor2);
    }//*/

    Ball head = Ball(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize, circleColor1);

    float itime = 0.0f;
    float dir = 1.0f;

    while (true) {
        SDL_Delay(1); //Wait each frame for consitancy

        //Clear Screen each frame
        SDL_SetRenderDrawColor(rend, 0, 60, 180, 255);
        SDL_RenderClear(rend);

        itime += 0.1f;

        // Initial Mouse State
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        Vector2 mouse = Vector2(mx, my);
        head.pos = mouse;

        /*head.pos = Vector2(dir * 5.0f + head.pos.x, HALF_HEIGHT + SDL_sinf(itime/2.0f)*100.0f);
        if (head.pos.x >= float(WIDTH)) {
            dir = -1.0f;
        } else if (head.pos.x <= 0.0f) {
            dir = 1.0f;
        }*/

        // Set positions of snake parts
        int n = sizeof(tailSegments)/sizeof(Ball);
        float mag = Helpful::Distance(head.pos, tailSegments[0].pos);
        if (mag > tailSegments[0].size) {
            tailSegments[0].pos = head.pos + (tailSegments[0].pos - head.pos).Normalized() * tailSegments[0].size;
        }

        for (int i = 1; i < n; i++) {
            mag = Helpful::Distance(tailSegments[i-1].pos, tailSegments[i].pos);
            if (mag > tailSegments[i].size) {
                tailSegments[i].pos = tailSegments[i-1].pos + (tailSegments[i].pos - tailSegments[i-1].pos).Normalized() * tailSegments[i].size;
            }
        }

        // Draw the snake
        for (int i = n; i >= 0; i--) {
            tailSegments[i].Draw(rend);
        }
        head.Draw(rend);

        SDL_RenderPresent(rend); // Draw everything to screen

        if (SDL_PollEvent( &windowEvent )) {
            switch(windowEvent.type ){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch(windowEvent.key.keysym.sym) {
                        case SDLK_0:
                            for (int i = 0; i < n; i++)
                            {
                                tailSegments[i].pos = Vector2(HALF_WIDTH, HALF_HEIGHT);
                            }
                            break;
                        default:
                            break;
                    }
                    break;

                /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    std::cout << "Window Falure" << std::endl;
                    goto Exit;

                default:
                    break;
            }
        }
    }
    Exit:

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( rend );
    SDL_Quit();

    return EXIT_SUCCESS;
} // mingw32-make