#include <SDL2/SDL.h>
#include "vector.cpp"

class Draw{
    public:
        /// Bresenham’s circle drawing algorithm
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
            while (relative.x - r >= -1) {
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
            while (relative.y - r >= -1) {
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

        /// Bresenham's Line Algorithm
        static void Line(SDL_Renderer *rend, Vector2 a, Vector2 b) {
            int x1, y1, x2, y2;
            if (a.x <= b.x) {
                x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y;
            } else {
                x2 = a.x, y2 = a.y, x1 = b.x, y1 = b.y;
            }
            // Take m = y2-y1/x2-x1 > 0.5 and multiply by 2*(x2-x1) to avoid f-point
            int slope = 2 * (y2 - y1);
            int dy = (y1 < y2) ? 1 : -1;
            int mult = 2 * (x2 - x1);
            int error = slope - (x2 - x1);
            for (int x = x1, y = y1; x <= x2; x++) {
                SDL_RenderDrawPoint(rend, x, y);
                error += slope;
                if (error >= 0) {
                    y+=dy;
                    error -= mult;
                }
            }
        }

        // Basic Functionality
        static void SetColor(SDL_Renderer *rend, Color c) {
            SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
        }
};
