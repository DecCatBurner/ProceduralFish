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

    float circleSize = 12.5f;

    Segment tailSegments[50];
    for (int i = 0; i < sizeof(tailSegments)/sizeof(Segment); i++) {
        tailSegments[i] = Segment(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(50-i)/50.0f, (i%2 == 1) ? Color(250, 100, 20, 255) : Color(200, 150, 30, 255));
    }
    Cord snake = Cord();
    snake.InitializeSegments(50, tailSegments);

    for (int i = 0; i < sizeof(tailSegments)/sizeof(Segment); i++) {
        tailSegments[i] = Segment(Vector2(HALF_WIDTH + 30, HALF_HEIGHT + 30), circleSize * float(50-i)/50.0f, (i%2 == 1) ? Color(30, 200, 100, 255) : Color(20, 220, 90, 255));
    }
    Cord snake2 = Cord();
    snake2.InitializeSegments(50, tailSegments);

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

        // Set positions of snake parts
        //snake.pos = snake.pos + mouse.Normalized()*25.0;
        snake.Move((mouse - origin).Normalized() * 0.5f);
        snake2.Move((mouse - origin + 30.0f).Normalized() * 0.5f);

        // Draw the snake
        snake.Draw(rend);
        snake2.Draw(rend);

        SDL_RenderPresent(rend); // Draw everything to screen

        if (SDL_PollEvent( &windowEvent )) {
            switch(windowEvent.type ){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch(windowEvent.key.keysym.sym) {
                        case SDLK_0:
                            snake.Move(snake.segments[0].pos - origin);
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