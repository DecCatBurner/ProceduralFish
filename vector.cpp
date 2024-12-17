#include <math.h>

class Vector2{
    public:
        float x, y;
        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float v) : x(v), y(v) {}
        Vector2(float x1, float y1) : x(x1), y(y1) {}
        Vector2(int x1, int y1) : x(float(x1)), y(float(y1)) {}
        constexpr Vector2(char s, float x1, float y1) : x(x1), y(y1) {}

        // Operations---------------------------------------------------------
        // Vec with Vec
        Vector2 operator + (const Vector2& a) const {
            Vector2 res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        Vector2 operator += (const Vector2& a) const {
            Vector2 res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        Vector2 operator - (const Vector2& a) const {
            Vector2 res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }
        Vector2 operator -= (const Vector2& a) const {
            Vector2 res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }

        // Vec with float
        Vector2 operator + (const float& a) const {
            Vector2 res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        Vector2 operator += (const float& a) const {
            Vector2 res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        Vector2 operator - (const float& a) const {
            Vector2 res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        Vector2 operator -= (const float& a) const {
            Vector2 res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        Vector2 operator * (const float& a) const {
            Vector2 res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        Vector2 operator *= (const float& a) const {
            Vector2 res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        Vector2 operator / (const float& a) const {
            Vector2 res;
            res.x = x / a;
            res.y = y / a;
            return res;
        }
        Vector2 operator /= (const float& a) const {
            Vector2 res;
            res.x = x / a;
            res.y = y / a;
            return res;
        }

        float Magnitude() {
            return sqrtf(x*x + y*y);
        }

        float SqMagnitude() {
            return x*x + y*y;
        }

        Vector2 Normalized() {
            float r = Magnitude();
            return Vector2(x/r,y/r);
        }
};

static constexpr Vector2 zero = Vector2(' ', 0.0f, 0.0f);
static constexpr Vector2 one = Vector2(' ', 1.0f, 1.0f);
static constexpr Vector2 up = Vector2(' ', 0.0f, 1.0f);
static constexpr Vector2 down = Vector2(' ', 0.0f, -1.0f);
static constexpr Vector2 right = Vector2(' ', 1.0f, 0.0f);
static constexpr Vector2 left = Vector2(' ', -1.0f, 0.0f);

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
        static Vector2 Lerp(Vector2 a, Vector2 b, float t) {
            return a*(1.0f-t) + b*t;
        }
        static float Lerp(float a, float b, float t) {
            return a*(1.0f-t) + b*t;
        }
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
};
