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

        virtual void Draw() {
            Draw::SetColor(color);
            Draw::CircleFilled(pos, size);
        }

        virtual void Draw(Vector2 dir) {
            //Draw::SetColor(color);
            //Draw::CircleFilled(pos, size);
        }
};

class HeadSegment : public Segment {
    public:
        HeadSegment() : Segment() {}
        HeadSegment(Vector2 pos, float radius, Color color) : Segment(pos, radius, color) {}

        void Draw(Vector2 dir) override {
            //Draw::SetColor(color);
            //Draw::CircleFilled(pos, size);
            Draw::SetColor(black);
            Draw::CircleFilled(pos + Vector2(dir.x * (0.707106781f) + dir.y * (0.707106781f), dir.x * (0.707106781f) - dir.y * (0.707106781f)), 7.0f);
            Draw::CircleFilled(pos + Vector2(dir.x * (0.707106781f) - dir.y * (0.707106781f), dir.x * (0.707106781f) + dir.y * (0.707106781f)), 7.0f);
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

        void Draw() {
            if (length == 0) {std::cout << "You need to initialize a cord first" << std::endl; return;}
            Vector2 diff = (segments[length-2].pos - segments[length-1].pos) * (segments[length-2].size / (segments[length-2].size + segments[length-1].size));
            Vector2 prevL = segments[length-1].pos - diff, prevR = segments[length-1].pos - diff;
            for (int i = length-1; i > 0; i--) {
                Vector2 diff = (segments[i-1].pos - segments[i].pos) * (segments[i].size / (segments[i-1].size + segments[i].size));
                segments[i].Draw(diff);
                Draw::SetColor(segments[i].color);
                Vector2 sideL = Vector2(diff.y*-1, diff.x) + segments[i].pos; // -90 degree
                Vector2 sideR = Vector2(diff.y, diff.x*-1) + segments[i].pos; // +90 degree
                Draw::TriangleFilled(sideR, prevL, sideL);
                Draw::TriangleFilled(prevR, prevL, sideR);
                prevL = sideL;
                prevR = sideR;
            }
            diff = (segments[0].pos - segments[1].pos) * (segments[0].size / (segments[0].size + segments[1].size));
            //Vector2 sideL = Vector2(diff.y, diff.x*-1);
            //Vector2 sideR = Vector2(diff.y*-1, diff.x);
            segments[0].Draw(diff);
            Draw::SetColor(segments[0].color);
            Draw::Line(segments[0].pos + diff, prevL);
            Draw::Line(segments[0].pos + diff, prevR);
        }
};