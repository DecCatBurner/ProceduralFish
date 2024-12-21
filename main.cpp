#include "boid.cpp"

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

    int tailTotal = 5;
    Segment tailSegments[3];
    tailSegments[0] = HeadSegment(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(tailTotal-SDL_abs(-tailTotal+4))/tailTotal, Color(200, 150, 30, 255));
    for (int i = 1; i < tailTotal; i++) {
        tailSegments[i] = Segment(Vector2(HALF_WIDTH, HALF_HEIGHT), circleSize * float(tailTotal-SDL_abs(i-tailTotal+4))/tailTotal, (i%2 == 1) ? Color(250, 100, 20, 255) : Color(200, 150, 30, 255));
    }

    int snakeTotal = 2;
    Cord snakes[2] = {Cord()};

    for (int i = 0; i < snakeTotal; i++) {
        float rot = float(i)/snakeTotal * 2.0f * M_PI;
        snakes[i].pos = origin + Vector2(SDL_sinf(rot), SDL_cosf(rot)) * 60.0f;
        snakes[i].velo = Vector2(SDL_sinf(rot), SDL_cosf(rot)) * Boid::maxVelo;
        snakes[i].InitializeSegments(tailTotal, tailSegments);
    }

    Boid::InitializeBoids(snakeTotal, snakes);

    float itime = 0.0f;
    bool pause = false;

    // Test line algorithm
    Draw::SetColor(green);
    //Draw::Line(origin, origin+oneone*10.0f);
    //Draw::Line(origin, origin+Vector2(1,-1)*10.0f);

    Draw::TriangleFilled(origin + Vector2(10, 10), origin + Vector2(1, -10), origin + Vector2(-10, 9));

    SDL_RenderPresent(rend);

    while (true) {
        SDL_Delay(1); //Wait each frame for consitancy

        itime += 0.1f;

        // Initial Mouse State
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        Vector2 mouse = Vector2(mx, my);
        if (!pause) {
            // Set velo of boids
            Boid::EvaluateBoids();
        }

        // Clear Screen each frame
        SDL_SetRenderDrawColor(rend, 0, 60, 180, 255);
        SDL_RenderClear(rend);

        // Draw scene
        Draw::SetColor(grey);
        Draw::CircleFilled(Vector2(200, 400), 50.0f);
        Draw::CircleFilled(Vector2(600, 100), 40.0f);
        Draw::CircleFilled(Vector2(650, 100), 10.0f);
        Draw::CircleFilled(Vector2(550, 150), 10.0f);
        Draw::CircleFilled(Vector2(620, 80), 5.0f);

        // Draw the snake
        Boid::DrawBoids();

        // Draw Overlay

        // Render scene
        SDL_RenderPresent( rend );
        // end of section */

        if (SDL_PollEvent( &windowEvent )) {
            switch(windowEvent.type ){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
                    switch(windowEvent.key.keysym.sym) {
                        case SDLK_p:
                            pause = !pause;
                            break;
                        case SDLK_c:
                            Draw::TakeScreenShot(window, itime);
                            std::cout << "Snap taken at: " << itime << std::endl;
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