#include "draw.cpp"

class Point {
    public:
        Vector2 pos;

        Point(Vector2 pos) : pos(pos) {}
};

class KinematicPoint : public Point {
    public:
        Vector2 velo;

        KinematicPoint(Vector2 pos, Vector2 velo) : Point(pos), velo(velo) {}
};

class Segment : public Point {
    public:
        Color color;
        float size, separation;

        Segment() : Point(origin), size(25.0f), separation(25.0f), color(white) {}
        Segment(Vector2 pos, float radius, Color color) : Point(pos), size(radius), separation(radius), color(color) {}
        Segment(Vector2 pos, float size, float separation, Color color) : Point(pos), size(size), separation(separation), color(color) {}

        void Draw(SDL_Renderer *rend) {
            Draw::SetColor(rend, color);
            Draw::CircleFilled(rend, pos, size);
        }
};

class Cord : public KinematicPoint {
    public:
        int length = 0;
        Segment* segments;

        Cord() : KinematicPoint(origin, zerozero) {}
        Cord(Vector2 pos) : KinematicPoint(pos, zerozero) {}
        Cord(Vector2 pos, Vector2 velo) : KinematicPoint(pos, velo) {}

        ~Cord() { delete[] segments; }

        void InitializeSegments(int len, Segment* segs) {
            length = len;
            segments = new Segment[len];
            for (int i = 0; i < len; i++) {
                segments[i] = segs[i];
            }
            segments[0].pos = pos;
        }

        void Move() {
            if (length == 0) {std::cout << "You need to initialize a cord first" << std::endl; return;}
            // Set positions of snake parts
            pos += velo;
            segments[0].pos = pos;
            float mag;
            for (int i = 1; i < length; i++) {
                mag = Helpful::Distance(segments[i-1].pos, segments[i].pos);
                if (mag > segments[i].separation + segments[i-1].separation) {
                    segments[i].pos = segments[i-1].pos + (segments[i].pos - segments[i-1].pos).Normalized() * (segments[i].separation + segments[i-1].separation);
                }
            }
        }

        void Move(Vector2 v) {
            if (length == 0) {std::cout << "You need to initialize a cord first" << std::endl; return;}
            // Set positions of snake parts
            pos += v;
            segments[0].pos = pos;
            float mag;
            for (int i = 1; i < length; i++) {
                mag = Helpful::Distance(segments[i-1].pos, segments[i].pos);
                if (mag > segments[i].separation + segments[i-1].separation) {
                    segments[i].pos = segments[i-1].pos + (segments[i].pos - segments[i-1].pos).Normalized() * (segments[i].separation + segments[i-1].separation);
                }
            }
        }

        void Draw(SDL_Renderer *rend) {
            if (length == 0) {std::cout << "You need to initialize a cord first" << std::endl; return;}
            for (int i = length-1; i >= 0; i--) {
                segments[i].Draw(rend);
            }
        }
};