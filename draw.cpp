#include <SDL2/SDL.h>
#include "vector.cpp"

const int WIDTH = 800, HEIGHT = 600;
const int HALF_WIDTH = 400, HALF_HEIGHT = 300;

class Draw{
    public:
        static void Circle8Points(SDL_Renderer *rend, Vector2 center, Vector2 relative) {
            // Draw points on each quadrant
            SDL_RenderDrawPointF(rend, center.x+relative.x, center.y+relative.y);
            SDL_RenderDrawPointF(rend, center.x-relative.x, center.y+relative.y);
            SDL_RenderDrawPointF(rend, center.x+relative.x, center.y-relative.y);
            SDL_RenderDrawPointF(rend, center.x-relative.x, center.y-relative.y);
            // Draw points again but flipped on x=y
            SDL_RenderDrawPointF(rend, center.x+relative.y, center.y+relative.x);
            SDL_RenderDrawPointF(rend, center.x-relative.y, center.y+relative.x);
            SDL_RenderDrawPointF(rend, center.x+relative.y, center.y-relative.x);
            SDL_RenderDrawPointF(rend, center.x-relative.y, center.y-relative.x);

        }
        static void Circle8Lines(SDL_Renderer *rend, Vector2 center, Vector2 relative) {
            // Draw lines that are and aren't flipped about x=y until reach x=0
            int r = 0;
            while (relative.x - r >= 0) {
                // Not flipped
                SDL_RenderDrawPointF(rend, center.x+relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rend, center.x-relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rend, center.x+relative.x, center.y-relative.y+r);
                SDL_RenderDrawPointF(rend, center.x-relative.x, center.y-relative.y+r);
                // Flipped
                SDL_RenderDrawPointF(rend, center.x+relative.y, center.y+relative.x-r);
                SDL_RenderDrawPointF(rend, center.x-relative.y, center.y+relative.x-r);
                SDL_RenderDrawPointF(rend, center.x+relative.y, center.y-relative.x+r);
                SDL_RenderDrawPointF(rend, center.x-relative.y, center.y-relative.x+r);
                r++;
            }
            // Continue for only lines that aren't flipped
            while (relative.y - r >= 0) {
                // Not flipped
                SDL_RenderDrawPointF(rend, center.x+relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rend, center.x-relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rend, center.x+relative.x, center.y-relative.y+r);
                SDL_RenderDrawPointF(rend, center.x-relative.x, center.y-relative.y+r);
                r++;
            }
        }
        static void CircleOutline(SDL_Renderer *rend, Vector2 pos, float r){
            float x, y = r;
            float d = 3.0f - (2.0f*r);
            for (x = 0; x <= y; x++){
                Circle8Points(rend, pos, Vector2(x,y));
                if (d < 0.0f) {
                    d = d + (4.0f*x)+6.0f;
                } else {
                    d = d + 4.0f*(x-y)+10.0f;
                    y--;
                }
            }
            Circle8Points(rend, pos, Vector2(x,y));
        }

        static void CircleFilled(SDL_Renderer *rend, Vector2 pos, float r){
            float x, y = r;
            float d = 3.0f - (2.0f*r);
            for (x = 0; x <= y; x++){
                Circle8Lines(rend, pos, Vector2(x,y));
                if (d < 0.0f) {
                    d = d + (4.0f*x)+6.0f;
                } else {
                    d = d + 4.0f*(x-y)+10.0f;
                    y--;
                }
            }
            Circle8Lines(rend, pos, Vector2(x,y));
        }

        static void SetColor(SDL_Renderer *rend, Color c) {
            SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
        }
};
