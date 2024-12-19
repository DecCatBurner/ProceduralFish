#include "obj.cpp"

//const int WIDTH = 800, HEIGHT = 600; this is declared in draw for simplicity

int main(int argsc, char *argsv[]) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow("Procedural Fish \u00A9DecCatBurner 2024", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, 1);

    Draw::SetRend(rend);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;
    // End init

    float circleSize = 12.5f;
    float maxVelo = 0.5f;
    float cohesionFactor = 0.00001f;
    float sight = 25.0f;
    float alignmentFactor = 0.001f;
    float turnFactor = 0.00625f;
    float separationDist = 15.0f;
    float separationFactor = 1.5f;

    int tailTotal = 5;
    Segment tailSegments[5];
    for (int i = 0; i < tailTotal; i++) {
        tailSegments[i] = Segment(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(tailTotal-SDL_abs(i-tailTotal+4))/tailTotal, (i%2 == 1) ? Color(250, 100, 20, 255) : Color(200, 150, 30, 255));
    }

    int snakeTotal = 20;
    Cord snakes[20] = {Cord()};

    for (int i = 0; i < snakeTotal; i++) {
        float rot = float(i)/snakeTotal * M_PI;
        snakes[i].pos = origin + Vector2(SDL_sinf(rot), SDL_cosf(rot)) * 30.0f;
        snakes[i].velo = Vector2(SDL_sinf(rot), SDL_cosf(rot)) * maxVelo;
        snakes[i].InitializeSegments(tailTotal, tailSegments);
    }

    float itime = 0.0f;
    float dir = 1.0f;
    bool pause = false;

    Draw::SetColor(red);
    Draw::Line(origin, origin+oneone*10.0f);
    Draw::Line(origin, origin+Vector2(1,-1)*10.0f);

    SDL_RenderPresent(rend);

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
            Vector2 rule3 = zerozero;
            for (int i = 0; i < snakeTotal; i++) {
                rule3 += snakes[i].velo;
            }
            rule3 /= snakeTotal;

            // Set velo of snakes
            for (int i = 0; i < snakeTotal; i++) {
                //snakes[i].Move((mouse - origin + i*10.0f).Normalized() * 0.25f);
                Vector2 rule1 = zerozero;
                Vector2 rule2 = zerozero;
                for (int j = 0; j < snakeTotal; j++) {
                    if (i == j) {continue;}
                    rule1 += (Helpful::SqDistance(snakes[i].pos, snakes[j].pos) < sight*sight) ? snakes[j].pos : zerozero;
                    rule2 -= (Helpful::SqDistance(snakes[i].pos, snakes[j].pos) < separationDist*separationDist) ? (snakes[j].pos - snakes[i].pos) : zerozero;
                }
                rule1 /= snakeTotal - 1;
                snakes[i].velo += rule1*cohesionFactor + rule2*separationFactor + rule3*alignmentFactor;
                if (snakes[i].pos.x > WIDTH - 50) { snakes[i].velo.x -= turnFactor; } else if (snakes[i].pos.x < 50) { snakes[i].velo.x += turnFactor; }
                if (snakes[i].pos.y > HEIGHT - 50) { snakes[i].velo.y -= turnFactor; } else if (snakes[i].pos.y < 50) { snakes[i].velo.y += turnFactor; }
                if (snakes[i].velo.SqMagnitude() > maxVelo*maxVelo) { snakes[i].velo = snakes[i].velo.Normalized() * maxVelo; }
                //std::cout << i << snakes[i].pos.x << snakes[i].pos.y << std::endl;
                snakes[i].Move();
            }
        }
        // Draw scene
        Draw::SetColor(grey);
        Draw::CircleFilled(Vector2(200, 400), 50.0f);
        Draw::CircleFilled(Vector2(600, 100), 40.0f);
        Draw::CircleFilled(Vector2(650, 100), 10.0f);
        Draw::CircleFilled(Vector2(550, 110), 10.0f);
        Draw::CircleFilled(Vector2(620, 80), 5.0f);

        // Draw the snake
        for (int i = 0; i < snakeTotal; i++) {
            snakes[i].Draw();
        }


        SDL_RenderPresent(rend); // Draw everything to screen */

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