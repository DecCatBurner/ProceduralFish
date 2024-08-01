#include "draw.cpp"


class SDFObj{
    public:
        int r, g, b, a;
        float val;

        SDFObj(int r1, int g1, int b1, int a1) {
            r = r1;
            g = g1;
            b = b1;
            a = a1;
            val = INFINITY;
        }

        SDFObj(int r1, int g1, int b1, int a1, float val1) {
            r = r1;
            g = g1;
            b = b1;
            a = a1;
            val = val1;
        }
};

class SDF{
    public:
        static float Lerp(int a, int b, float t) {
            return (1 - t) * a + t * b;
        }
        // Basic conjuctions
        static SDFObj Intersect(SDFObj a, SDFObj b) {
            if (a.val < b.val) {
                return a;
            }
            return b;
        }
        static SDFObj Subtract(SDFObj a, SDFObj b) {
            if (a.val < b.val) {
                return b;
            }
            return a;
        }
        static SDFObj SmIntersect(SDFObj a, SDFObj b, float k = 32) {
            float res = expf(-k*a.val) + expf(-k*b.val);
            float blend = -logf((0.0001 > res) ? 0.0001 : res) / k;
            return SDFObj(Lerp(a.r, b.r, blend), Lerp(a.g, b.g, blend), Lerp(a.b, b.b, blend), Lerp(a.a, b.a, blend), blend);
        }
        // SDFs
        static float Circle(int posx, int posy, int rad){
            return sqrtf(posx * posx + posy * posy) - rad;
        }
        // Map
        static void Map(SDL_Renderer *rend, int x, int y) {
            // Declare Starting variables
            SDFObj fin = SDFObj(0, 0, 0, 255, 0);

            SDFObj a = SDFObj(255, 0, 255, 255);
            a.val = Circle(x - 400, y - 300, 100);
            
            SDFObj b = SDFObj(0, 255, 0, 255, Circle(x - 500, y - 300, 50));

            a = Intersect(a, b);

            fin = Intersect(a, fin);

            // Render the pixel
            SDL_SetRenderDrawColor(rend, fin.r, fin.g, fin.b, fin.a);
            SDL_RenderDrawPoint(rend, x, y);
        }
        static void CompleteMap(SDL_Renderer *rend){
            for (int x = 0; x < 800; x++) {
                for (int y = 0; y < 600; y++) {
                    Map(rend, x, y);
                }
            }
        }
};