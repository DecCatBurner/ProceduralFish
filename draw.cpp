#include <SDL2/SDL.h>
#include "vector.cpp"

const int WIDTH = 800, HEIGHT = 600;
const int HALF_WIDTH = 400, HALF_HEIGHT = 300;

class Draw{
    public:
        static void Circle(SDL_Renderer *rend, Vec2<int> pos, int rad){
            for (int x = pos.x - rad; x < pos.x + rad; x++){
                for (int y = pos.y - rad; y < pos.y + rad; y++){
                    int sdf = Vec::Length(x-pos.x, y-pos.y) - rad;
                    if (sdf < 0){
                        SDL_RenderDrawPoint(rend, x, y);
                    }
                }
            }
        }
        static void CircleOutline(SDL_Renderer *rend, Vec2<int> pos, int rad, int str){
            int off = rad + str;
            for (int x = pos.x - off; x < pos.x + off; x++){
                for (int y = pos.y - off; y < pos.y + off; y++){
                    int sdf = Vec::Length(x-pos.x, y-pos.y) - rad;
                    if (abs(sdf) < str){
                        SDL_RenderDrawPoint(rend, x, y);
                    }
                }
            }
        }
};
