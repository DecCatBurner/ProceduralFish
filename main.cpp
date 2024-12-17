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
    float maxVelo = 2.0f;
    float turnfactor = 0.125f;

    Segment tailSegments[50];
    for (int i = 0; i < sizeof(tailSegments)/sizeof(Segment); i++) {
        tailSegments[i] = Segment(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(50-i)/50.0f, (i%2 == 1) ? Color(250, 100, 20, 255) : Color(200, 150, 30, 255));
    }

    int snakeTotal = 4;
    Cord snakes[4] = {Cord(), Cord(), Cord(), Cord()};

    for (int i = 0; i < snakeTotal; i++) {
        float rot = float(i)/snakeTotal * M_PI;
        snakes[i].pos = origin + Vector2(SDL_sinf(rot), SDL_cosf(rot)) * 10.0f;
        snakes[i].velo = Vector2(SDL_sinf(rot), SDL_cosf(rot)) * 10.0f;
        snakes[i].InitializeSegments(50, tailSegments);
    }

    float itime = 0.0f;
    float dir = 1.0f;
    bool pause = false;

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
        if (!pause) {
            // Find rules
            Vector2 rule1 = zerozero;
            Vector2 rule3 = zerozero;
            for (int i = 0; i < snakeTotal; i++) {
                //rule1 += snakes[i].pos;
                rule3 += snakes[i].velo;
            }
            //rule1 /= snakeTotal;
            rule3 /= snakeTotal;

            // Set velo of snakes
            for (int i = 0; i < snakeTotal; i++) {
                //snakes[i].Move((mouse - origin + i*10.0f).Normalized() * 0.25f);
                Vector2 rule2 = zerozero;
                for (int j = 0; j < snakeTotal; j++) {
                    if (i == j) {continue;}
                    rule2 -= (Helpful::SqDistance(snakes[i].pos, snakes[j].pos) < 100.0f) ? (snakes[j].pos - snakes[i].pos) : zerozero;
                }
                snakes[i].velo += rule2*3.0f + rule3*0.001f;
                if (snakes[i].pos.x > WIDTH - 50) { snakes[i].velo.x -= turnfactor; } else if (snakes[i].pos.x < 50) { snakes[i].velo.x += turnfactor; }
                if (snakes[i].pos.y > HEIGHT - 50) { snakes[i].velo.y -= turnfactor; } else if (snakes[i].pos.y < 50) { snakes[i].velo.y += turnfactor; }
                if (snakes[i].velo.SqMagnitude() > maxVelo*maxVelo) { snakes[i].velo = snakes[i].velo.Normalized() * maxVelo; }
                //std::cout << i << snakes[i].pos.x << snakes[i].pos.y << std::endl;
                snakes[i].Move();
            }
        }
        // Draw the snake
        for (int i = 0; i < snakeTotal; i++) {
            snakes[i].Draw(rend);
        }

        SDL_RenderPresent(rend); // Draw everything to screen

        if (SDL_PollEvent( &windowEvent )) {
            switch(windowEvent.type ){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                    switch(windowEvent.key.keysym.sym) {
                        case SDLK_0:
                            pause = !pause;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
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