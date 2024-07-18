#include <iostream>
#include <SDL2/SDL.h>

class Draw{
    public:
        static void Circle(SDL_Renderer *rend, int posx, int posy, int rad){
            for (int x = 0; x < 800; x++){
                for (int y = 0; y < 800; y++){
                    int sdf = SDL_sqrt((x-posx)*(x-posx) + (y-posy)*(y-posy)) - rad;
                    if (sdf < 0){
                        SDL_RenderDrawPoint(rend, x, y);
                    }
                }
            }
        }
        static void CircleOutline(SDL_Renderer *rend, int posx, int posy, int rad, int str){
            for (int x = 0; x < 800; x++){
                for (int y = 0; y < 800; y++){
                    int sdf = SDL_sqrt((x-posx)*(x-posx) + (y-posy)*(y-posy)) - rad;
                    if (SDL_abs(sdf) < str){
                        SDL_RenderDrawPoint(rend, x, y);
                    }
                }
            }
        }
};

class SDFObj{
    public:
        int r, g, b, a;
        int val;

        SDFObj(int r1, int g1, int b1, int a1) {
            r = r1;
            g = g1;
            b = b1;
            a = a1;
            val = 2147483647;
        }
};

class SDF{
    public:
        // Basic conjuctions
        static SDFObj Min(SDFObj a, SDFObj b) {
            if (a.val < b.val) {
                return a;
            }
            return b;
        }
        // SDFs
        static int Circle(int posx, int posy, int rad){
            return SDL_sqrt(posx * posx + posy * posy) - rad;
        }
        // Map
        static void Map(SDL_Renderer *rend, int x, int y) {
            // Declare Starting variables
            SDFObj fin = SDFObj(0, 0, 0, 255);
            fin.val = 1;

            SDFObj a = SDFObj(255, 0, 255, 255);
            a.val = Circle(x - 400, y - 300, 10);

            fin = Min(a, fin);

            // Render the pixel
            SDL_SetRenderDrawColor(rend, fin.r, fin.g, fin.b, fin.a);
            SDL_RenderDrawPoint(rend, x, y);
        }
};

const int WIDTH = 800, HEIGHT = 600;

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

    while (true) {
        SDL_Delay(10);
        //iTime = SDL_GetTicks64() * 0.001f;

        SDL_SetRenderDrawColor(rend, 0, 60, 180, 255);
        SDL_RenderClear(rend);
        for (int x = 0; x < 800; x++){
            for (int y = 0; y < 800; y++){
                SDF::Map(rend, x, y);
            }
        }
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