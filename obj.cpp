#include "draw.cpp"

class Object{
    public:
        Vector2 pos;
        float size;

        Object(Vector2 pos, float size) : pos(pos), size(size) {}
};

class Ball : public Object {
    public:
        Color color;

        Ball() : Object(Vector2(HALF_WIDTH, HALF_HEIGHT), 50.0f), color(white) {}
        Ball(Vector2 pos, float size, Color color) : Object(pos, size), color(color) {}

        void Draw(SDL_Renderer *rend) {
            Draw::SetColor(rend, color);
            Draw::CircleFilled(rend, pos, size);
        }
};