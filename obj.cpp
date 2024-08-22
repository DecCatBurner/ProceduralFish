#include "baseObj.cpp"

class Chain : public Ball{
    public:
        // Properties
        int maxDist = 20;
        Ball segments[5];
        // Declare
        /*Chain() : firstSegment(nullptr), Ball() {}
        Chain(Segment segment) : firstSegment(&segment), Ball() {}
        Chain(Vec4<int> color, Segment* segment) : Ball(color), firstSegment(segment) {}
        Chain(int size, Vec2<int> pos, Vec2<int> velo, Vec4<int> color, Segment* segment) : Ball(size, pos, velo, color), firstSegment(segment) {}
        */
        Chain() : Ball() {}
        // Functions
        /*void AddSegment(Segment* toAdd) {
            Segment* currentSegment = firstSegment;
            Segment* nextSegment = currentSegment->nextSegment;
            while (nextSegment != nullptr) {
                currentSegment = nextSegment;
                nextSegment = currentSegment->nextSegment;
            }
            nextSegment = toAdd;
        }*/

        void Move() {
            // Move the focus
            pos += velo;
            bound();
            // Move segments
            Vec2<int> prevPos = pos;
            for (Ball ball : segments) {
                ball.SetPos(prevPos + Vec::Normalize(prevPos - ball.pos) * maxDist);
                prevPos = ball.pos;
            }
        }

        void Move(Vec2<int> v) {
            // Move the focus
            pos += v;
            bound();
            // Move segments
            Vec2<int> prevPos = pos;
            for (Ball ball : segments) {
                ball.SetPos(prevPos + Vec::Normalize(prevPos - ball.pos) * maxDist);
                prevPos = ball.pos;
            }
        }

        void SetPos(Vec2<int> newPos) {
            // Move the focus
            pos = newPos;
            // Move segments
            Vec2<int> prevPos = pos;
            for (Ball ball : segments) {
                ball.SetPos(prevPos + Vec::Normalize(prevPos - ball.pos) * maxDist);
                prevPos = ball.pos;
            }
        }

        void Draw(SDL_Renderer *rend){
            SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
            Draw::Circle(rend, pos, size);

            for (Ball b : segments) {
                b.Draw(rend, color);
            }
        }
};