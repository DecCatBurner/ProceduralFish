#include <SDL2/SDL.h>
#include "vector.cpp"

class Draw{
    public:
        static inline SDL_Renderer *rendGlobal = nullptr;
        static void SetRend(SDL_Renderer *rend) {
            rendGlobal = rend;
        }
        /// Bresenham’s circle drawing algorithm
        static void Circle8Points(Vector2 center, Vector2 relative) {
            // Draw points on each quadrant
            SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y+relative.y);
            SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y+relative.y);
            SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y-relative.y);
            SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y-relative.y);
            // Draw points again but flipped on x=y
            SDL_RenderDrawPointF(rendGlobal, center.x+relative.y, center.y+relative.x);
            SDL_RenderDrawPointF(rendGlobal, center.x-relative.y, center.y+relative.x);
            SDL_RenderDrawPointF(rendGlobal, center.x+relative.y, center.y-relative.x);
            SDL_RenderDrawPointF(rendGlobal, center.x-relative.y, center.y-relative.x);

        }

        static void Circle8Lines(Vector2 center, Vector2 relative) {
            // Draw lines that are and aren't flipped about x=y until reach x=0
            int r = 0;
            while (relative.x - r >= -1) {
                // Not flipped
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y-relative.y+r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y-relative.y+r);
                // Flipped
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.y, center.y+relative.x-r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.y, center.y+relative.x-r);
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.y, center.y-relative.x+r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.y, center.y-relative.x+r);
                r++;
            }
            // Continue for only lines that aren't flipped
            while (relative.y - r >= -1) {
                // Not flipped
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y+relative.y-r);
                SDL_RenderDrawPointF(rendGlobal, center.x+relative.x, center.y-relative.y+r);
                SDL_RenderDrawPointF(rendGlobal, center.x-relative.x, center.y-relative.y+r);
                r++;
            }
        }

        static void CircleOutline(Vector2 pos, float r){
            float x, y = r;
            float d = 3.0f - (2.0f*r);
            for (x = 0; x <= y; x++){
                Circle8Points(pos, Vector2(x,y));
                if (d < 0.0f) {
                    d = d + (4.0f*x)+6.0f;
                } else {
                    d = d + 4.0f*(x-y)+10.0f;
                    y--;
                }
            }
            Circle8Points(pos, Vector2(x,y));
        }

        static void CircleFilled(Vector2 pos, float r){
            float x, y = r;
            float d = 3.0f - (2.0f*r);
            for (x = 0; x <= y; x++){
                Circle8Lines(pos, Vector2(x,y));
                if (d < 0.0f) {
                    d = d + (4.0f*x)+6.0f;
                } else {
                    d = d + 4.0f*(x-y)+10.0f;
                    y--;
                }
            }
            Circle8Lines(pos, Vector2(x,y));
        }

        /// Bresenham's Line Algorithm
        static void Line(Vector2 a, Vector2 b) {
            // Take m = (y2-y1)/(x2-x1) > 0.5 and multiply by 2*(x2-x1) to avoid f-point
            int dydt = SDL_abs(a.y - b.y); // Change in y per step
            int dxdt = SDL_abs(a.x - b.x); // Change in x per step
            // Declare var for use
            int x1, y1, x2, y2;
            if (dydt > dxdt) { // When the change in y is greater
                if (a.y <= b.y) {
                    x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y;
                } else {
                    x2 = a.x, y2 = a.y, x1 = b.x, y1 = b.y;
                }
                int dx = (x1 < x2) ? 1 : -1;
                int error = 2*dxdt - dydt;
                for (int x = x1, y = y1; y <= y2; y++) {
                    SDL_RenderDrawPoint(rendGlobal, x, y);
                    error += 2*dxdt;
                    if (error >= 0) {
                        x+=dx;
                        error -= 2*dydt;
                    }
                    //std::cout << x << "," << y << "e" << error << std::endl;
                }
            } else {
                if (a.x <= b.x) {
                    x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y;
                } else {
                    x2 = a.x, y2 = a.y, x1 = b.x, y1 = b.y;
                }
                int dy = (y1 < y2) ? 1 : -1;
                int error = 2*dydt - dxdt;
                for (int x = x1, y = y1; x <= x2; x++) {
                    SDL_RenderDrawPoint(rendGlobal, x, y);
                    error += 2*dydt;
                    if (error >= 0) {
                        y+=dy;
                        error -= 2*dxdt;
                    }
                    //std::cout << x << "," << y << "e" << error << std::endl;
                }
            }
        }

        /// Use vertical pairings, a.y == b.y 
        static void FilledDouble(Vector2 a, Vector2 mid, Vector2 b) {
            // Take m = (y2-y1)/(x2-x1) > 0.5 and multiply by 2*(x2-x1) to avoid f-point
            IntVector2 dAdt = IntVector2(SDL_abs(a.x - mid.x), SDL_abs(a.y - mid.y)); // Change in the line (x && y) per step
            IntVector2 dBdt = IntVector2(SDL_abs(b.x - mid.x), SDL_abs(b.y - mid.y)); // Change in the line (x && y) per step
            // Declare var for use
            IntVector2 A1, A2, B1, B2;
            
            if (a.x <= mid.x) {
                A1 = IntVector2(a);
                A2 = IntVector2(mid);
            } else {
                A2 = IntVector2(a);
                A1 = IntVector2(mid);
            }
            if (b.x <= mid.x) {
                B1 = IntVector2(b);
                B2 = IntVector2(mid);
            } else {
                B2 = IntVector2(b);
                B1 = IntVector2(mid);
            }
            int Ady = (A1.y < A2.y) ? 1 : -1; // Step direction for A.y
            int Bdy = (B1.y < B2.y) ? 1 : -1; // Step direction for A.y
            int errorA = 2*dAdt.y - dAdt.x; // Track how close to next jump
            int errorB = 2*dBdt.y - dBdt.x; // Track how close to next jump
            for (int x = A1.x, y = A1.y; x <= A2.x; x++) { // Remember A.y == B.y
                bool drawline = false;
                SDL_RenderDrawPoint(rendGlobal, x, y);
                errorA += 2*dAdt.y;
                errorB += 2*dBdt.y;
                Loop:
                if (errorA >= 0) {
                    y+=Ady;
                    errorA -= 2*dAdt.x;
                    drawline = true;
                }
                if (errorB >= 0) {
                    y+=Bdy;
                    errorB -= 2*dBdt.x;
                    drawline = true;
                }
                if (drawline) {
                    for (int slide = x; slide >= A1.x; slide--) {
                        SDL_RenderDrawPoint(rendGlobal, slide, y);
                    }
                    if (errorA >= 0 || errorB >= 0) {
                        goto Loop;
                    }
                }
                //std::cout << x << "," << y << "e" << error << std::endl;
            }
        }

        /// Quad Half-Edge Algorithm
        static constexpr int q = 8; // Save compute, must be pow-2
        // Points must be clockwise (based on half-edge algorithm)
        static void TriangleFilled(Vector2 a, Vector2 b, Vector2 c) {
            // Split triange into two with flat top
            // Handle bresenham double abad

            // Handle bresenham double cbcd
        }

        // Basic Functionality
        static void SetColor(Color c) {
            SDL_SetRenderDrawColor(rendGlobal, c.r, c.g, c.b, c.a);
        }

        static void TakeScreenShot(SDL_Window* window, float itime) {
            SDL_Surface *sshot = SDL_GetWindowSurface(window);
            SDL_RenderReadPixels(rendGlobal, NULL, SDL_GetWindowPixelFormat(window), sshot->pixels, sshot->pitch);
            std::string file = ("Screenshots\\screenshot" + std::to_string(itime) + ".bmp");
            SDL_SaveBMP(sshot, file.c_str());
            SDL_FreeSurface(sshot);
        }
};
