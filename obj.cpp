#include "draw.cpp"

class Ball{
    int size = 10;
    Vec2<int> pos;
    Vec2<int> velo;
    Vec4<int> color;
    public:
        // Declare
        Ball() : size(10), pos(HALF_WIDTH, HALF_HEIGHT), velo(0,0), color(255, 0, 255, 255) {}
        Ball(int s1, int x1, int y1, int vx1, int vy1, int r1, int g1, int b1, int a1 = 255) : size(s1), pos(x1, y1), velo(vx1, vy1), color(r1, g1, b1, a1) {}
        Ball(int s1, Vec2<int> pos1, Vec2<int> velo1, int r1, int g1, int b1, int a1 = 255) : size(s1), pos(pos1), velo(velo1), color(r1, g1, b1, a1) {}
        
        Ball(int s1, int x1, int y1, int vx1, int vy1, Vec4<int> color1) : size(s1), pos(x1, y1), velo(vx1, vy1), color(color1) {}
        Ball(int s1, Vec2<int> pos1, Vec2<int> velo1, Vec4<int> color1) : size(s1), pos(pos1), velo(velo1), color(color1) {}
        Ball(int s1, int x1, int y1, int vx1, int vy1, int val) : size(s1), pos(x1, y1), velo(vx1, vy1), color(val, val, val, 255) {}
        Ball(int s1, Vec2<int> pos1, Vec2<int> velo1, int val) : size(s1), pos(pos1), velo(velo1), color(val, val, val, 255) {}
        Ball(int s1, int x1, int y1, int val) : size(s1), pos(x1, y1), velo(0, 0), color(val, val, val, 255) {}
        Ball(int s1, Vec2<int> pos1, int val) : size(s1), pos(pos1), velo(0,0), color(val, val, val, 255) {}
        // Funct
        void Move() {
            pos = Vec2(pos.x + velo.x, pos.y + velo.y);
            bound();
        }
        void SetPos(int px, int py) {
            pos = Vec2(px, py);
        }
        void SetPos(Vec2<int> pos1) {
            pos = pos1;
        }
        void SetSpeed(int vx1, int vy1) {
            velo = Vec2(vx1, vy1);
        }
        void SetSpeed(Vec2<int> velo1) {
            velo = velo1;
        }
        void bound() {
            if (pos.x > WIDTH || pos.x < 0){
                velo.x *= -1;
                while (pos.x > WIDTH || pos.x < 0) {
                    pos.x += velo.x;
                }
            }
            if (pos.y > HEIGHT || pos.y < 0){
                velo.y *= -1;
                while (pos.y > HEIGHT || pos.y < 0) {
                    pos.y += velo.y;
                }
            }
        }
        // Draw
        void Draw(SDL_Renderer *rend){
            SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
            Draw::Circle(rend, pos, size);
        }
};