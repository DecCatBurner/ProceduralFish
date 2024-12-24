#include <math.h>
#include <iostream>

// Screen const
const int WIDTH = 800, HEIGHT = 600;
const int HALF_WIDTH = 400, HALF_HEIGHT = 300;

class Vector2{
    public:
        float x, y;
        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float v) : x(v), y(v) {}
        Vector2(float x1, float y1) : x(x1), y(y1) {}
        Vector2(int x1, int y1) : x(float(x1)), y(float(y1)) {}
        constexpr Vector2(char s, float x1, float y1) : x(x1), y(y1) {}
        constexpr Vector2(char s, int x1, int y1) : x(float(x1)), y(float(y1)) {}

        // Operations---------------------------------------------------------
        // Vec with Vec
        Vector2 operator + (const Vector2& a) const {
            Vector2 res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        Vector2& operator += (const Vector2& a) {
            this->x = x + a.x;
            this->y = y + a.y;
            return *this;
        }
        Vector2 operator - (const Vector2& a) const {
            Vector2 res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }
        Vector2& operator -= (const Vector2& a) {
            this->x = x - a.x;
            this->y = y - a.y;
            return *this;
        }

        // Vec with float
        Vector2 operator + (const float& a) const {
            Vector2 res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        Vector2& operator += (const float& a) {
            this->x = x + a;
            this->y = y + a;
            return *this;
        }
        Vector2 operator - (const float& a) const {
            Vector2 res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        Vector2& operator -= (const float& a) {
            this->x = x - a;
            this->y = y - a;
            return *this;
        }
        Vector2 operator * (const float& a) const {
            Vector2 res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        Vector2& operator *= (const float& a) {
            this->x = x * a;
            this->y = y * a;
            return *this;
        }
        Vector2 operator / (const float& a) const {
            Vector2 res;
            res.x = x / a;
            res.y = y / a;
            return res;
        }
        Vector2& operator /= (const float& a) {
            this->x = x / a;
            this->y = y / a;
            return *this;
        }

        float Magnitude() {
            return sqrtf(x*x + y*y);
        }

        float SqMagnitude() {
            return x*x + y*y;
        }

        Vector2 Normalized() {
            float r = Magnitude();
            if (r == 0.0f) {return Vector2(0,0);}
            return Vector2(x/r,y/r);
        }
};

std::ostream& operator << (std::ostream &os, Vector2 const &a) { 
    return os << "(" << a.x << ", " << a.y << ")";
}

static constexpr Vector2 zerozero = Vector2(' ', 0.0f, 0.0f);
static constexpr Vector2 oneone = Vector2(' ', 1.0f, 1.0f);
static constexpr Vector2 origin = Vector2(' ', HALF_WIDTH, HALF_HEIGHT);
static constexpr Vector2 up = Vector2(' ', 0.0f, 1.0f);
static constexpr Vector2 down = Vector2(' ', 0.0f, -1.0f);
static constexpr Vector2 right = Vector2(' ', 1.0f, 0.0f);
static constexpr Vector2 left = Vector2(' ', -1.0f, 0.0f);

class IntVector2{
    public:
        int x, y;

        IntVector2() : x(0), y(0) {}
        IntVector2(int v) : x(v), y(v) {}
        IntVector2(int x, int y) : x(x), y(y) {}
        IntVector2(float x, float y) : x(SDL_round(x)), y(SDL_round(y)) {}
        IntVector2(Vector2 a) : x(int(a.x)), y(int(a.y)) {}

                // Operations---------------------------------------------------------
        // Vec with Vec
        IntVector2 operator + (const IntVector2& a) const {
            IntVector2 res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        IntVector2& operator += (const IntVector2& a) {
            this->x = x + a.x;
            this->y = y + a.y;
            return *this;
        }
        IntVector2 operator - (const IntVector2& a) const {
            IntVector2 res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }
        IntVector2& operator -= (const IntVector2& a) {
            this->x = x - a.x;
            this->y = y - a.y;
            return *this;
        }

        // Vec with float
        IntVector2 operator + (const int& a) const {
            IntVector2 res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        IntVector2& operator += (const int& a) {
            this->x = x + a;
            this->y = y + a;
            return *this;
        }
        IntVector2 operator - (const int& a) const {
            IntVector2 res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        IntVector2& operator -= (const int& a) {
            this->x = x - a;
            this->y = y - a;
            return *this;
        }
        IntVector2 operator * (const int& a) const {
            IntVector2 res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        IntVector2& operator *= (const int& a) {
            this->x = x * a;
            this->y = y * a;
            return *this;
        }
        IntVector2 operator / (const int& a) const {
            IntVector2 res;
            res.x = x / a;
            res.y = y / a;
            return res;
        }
        IntVector2& operator /= (const int& a) {
            this->x = x / a;
            this->y = y / a;
            return *this;
        }
        IntVector2 operator & (const int& a) const {
            IntVector2 res;
            res.x = x & a;
            res.y = y & a;
            return res;
        }
        IntVector2& operator &= (const int& a) {
            this->x = x & a;
            this->y = y & a;
            return *this;
        }

        // Bitwise
        IntVector2 operator << (const int& a) const {
            IntVector2 res;
            res.x = x << a;
            res.y = y << a;
            return res;
        }
        IntVector2 operator >> (const int& a) const {
            IntVector2 res;
            res.x = x >> a;
            res.y = y >> a;
            return res;
        }
};

std::ostream& operator << (std::ostream &os, IntVector2 const &a) { 
    return os << "Int(" << a.x << ", " << a.y << ")";
}

class Color{
    public:
        int r, g, b, a;
        Color() : r(0), g(0), b(0), a(0) {}
        Color(int v) : r(v), g(v), b(v), a(255) {}
        Color(int r1, int g1, int b1, int a1 = 255) : r(r1), g(g1), b(b1), a(a1) {}

        constexpr Color(char s, int r1, int g1, int b1, int a1 = 255) : r(r1), g(g1), b(b1), a(a1) {}
};

static constexpr Color black = Color(' ', 0, 0, 0);
static constexpr Color red = Color(' ', 255, 0, 0);
static constexpr Color yellow = Color(' ', 255, 255, 0);
static constexpr Color green = Color(' ', 0, 255, 0);
static constexpr Color cyan = Color(' ', 0, 255, 255);
static constexpr Color blue = Color(' ', 0, 0, 255);
static constexpr Color magenta = Color(' ', 255, 0, 255);
static constexpr Color gray = Color(' ', 125, 125, 125);
static constexpr Color grey = Color(' ', 125, 125, 125);
static constexpr Color white = Color(' ', 255, 255, 255);

class Helpful{
    public:
        // Interpolation
        static Vector2 Lerp(Vector2 a, Vector2 b, float t) {
            return a*(1.0f-t) + b*t;
        }
        static float Lerp(float a, float b, float t) {
            return a*(1.0f-t) + b*t;
        }
        // Magnitudes and Lengths
        static float Magnitude(float x, float y) {
            return sqrtf(x*x + y*y);
        }
        static float SqMagnitude(float x, float y) {
            return x*x + y*y;
        }
        static int Magnitude(int x, int y) {
            return int(sqrt(x*x + y*y));
        }
        static int SqMagnitude(int x, int y) {
            return x*x + y*y;
        }
        static float Distance(Vector2 a, Vector2 b) {
            return Magnitude(a.x - b.x, a.y - b.y);
        }
        static float SqDistance(Vector2 a, Vector2 b) {
            return SqMagnitude(a.x - b.x, a.y - b.y);
        }
        // Min || Max
        static int Min(int a, int b) {
            return (a <= b) ? a : b;
        }
        static int Max(int a, int b) {
            return (a >= b) ? a : b;
        }
};

/*
 * I don't care to impliment rotation matrices
 * so remember that r(pheta) = [ [cos -sin] [sin cos] ] in form [ [a b] [c d] ]
 * and is applied to a vector as [x y] * [ [cos -sin] [sin cos] ] = [(x*cos + y*sin) (x*cos - y*sin)]
*/
