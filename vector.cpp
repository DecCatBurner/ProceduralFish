#include <math.h>

template <typename T = int> class Vec2{
    public:
        T x, y;
        Vec2() : x(0), y(0) {}
        Vec2(T v) : x(v), y(v) {}
        Vec2(T x1, T y1) : x(x1), y(y1) {}
        constexpr Vec2(char s, T x1, T y1) : x(x1), y(y1) {}

        static constexpr Vec2 zero = Vec2(' ', 0, 0);
        static constexpr Vec2 one = Vec2(' ', 1, 1);
        static constexpr Vec2 up = Vec2(' ', 0, 1);
        static constexpr Vec2 down = Vec2(' ', 0, -1);
        static constexpr Vec2 right = Vec2(' ', 1, 0);
        static constexpr Vec2 left = Vec2(' ', -1, 0);

        Vec2<int> operator + (const Vec2<int>& a) const {
            Vec2<int> res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        Vec2<int> operator += (const Vec2<int>& a) const {
            Vec2<int> res;
            res.x = x + a.x;
            res.y = y + a.y;
            return res;
        }
        Vec2<int> operator - (const Vec2<int>& a) const {
            Vec2<int> res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }
        Vec2<int> operator -= (const Vec2<int>& a) const {
            Vec2<int> res;
            res.x = x - a.x;
            res.y = y - a.y;
            return res;
        }
        
        Vec2<int> operator + (const int& a) const {
            Vec2<int> res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        Vec2<int> operator - (const int& a) const {
            Vec2<int> res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        Vec2<int> operator * (const int& a) const {
            Vec2<int> res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        Vec2<int> operator / (const int& a) const {
            /*Vec2<int> res;
            res.x = x / a;
            res.y = y / a;*/
            return Vec2<int>(x/a, y/a);
        }

        Vec2<int> operator + (const float& a) const {
            Vec2<int> res;
            res.x = x + a;
            res.y = y + a;
            return res;
        }
        Vec2<int> operator - (const float& a) const {
            Vec2<int> res;
            res.x = x - a;
            res.y = y - a;
            return res;
        }
        Vec2<int> operator * (const float& a) const {
            Vec2<int> res;
            res.x = x * a;
            res.y = y * a;
            return res;
        }
        Vec2<int> operator / (const float& a) const {
            Vec2<int> res;
            res.x = x / a;
            res.y = y / a;
            return res;
        }
};

/*template <> class Vec2<int> {
    public:
        int x, y;
        
};*/

template <typename T = int> class Vec3{
    public:
        T x, y, z;
        Vec3() : x(0), y(0), z(0) {}
        Vec3(T v) : x(v), y(v), z(v) {}
        Vec3(T x1, T y1, T z1) : x(x1), y(y1), z(z1) {}
        Vec3(T x1, T y1) : x(x1), y(y1), z(0) {}
        Vec3(Vec2<T> vec) : x(vec.x), y(vec.y), z(0) {}

        constexpr Vec3(char s, T x1, T y1, T z1) : x(x1), y(y1), z(z1) {}

        static constexpr Vec3 zero = Vec3(' ', 0, 0, 0);
        static constexpr Vec3 one = Vec3(' ', 1, 1, 1);
};

template <typename T = int> class Vec4{
    public:
        T r, g, b, a;
        Vec4() : r(0), g(0), b(0), a(0) {}
        Vec4(T v) : r(v), g(v), b(v), a(255) {}
        Vec4(T r1, T g1, T b1, T a1 = 255) : r(r1), g(g1), b(b1), a(a1) {}
        //Vec4(T r1, T g1, T b1) : r(r1), g(g1), b(b1), a(255) {}
        Vec4(Vec3<T> color) : r(color.x), g(color.y), b(color.z), a(255) {}
        Vec4(Vec3<T> color, T a1 = 255) : r(color.x), g(color.y), b(color.z), a(a1) {}

        constexpr Vec4(char s, T r1, T g1, T b1, T a1 = 255) : r(r1), g(g1), b(b1), a(a1) {}

        static constexpr Vec4 black = Vec4(' ', 0, 0, 0);
        static constexpr Vec4 red = Vec4(' ', 255, 0, 0);
        static constexpr Vec4 yellow = Vec4(' ', 255, 255, 0);
        static constexpr Vec4 green = Vec4(' ', 0, 255, 0);
        static constexpr Vec4 cyan = Vec4(' ', 0, 255, 255);
        static constexpr Vec4 blue = Vec4(' ', 0, 0, 255);
        static constexpr Vec4 magenta = Vec4(' ', 255, 0, 255);
        static constexpr Vec4 gray = Vec4(' ', 125, 125, 125);
        static constexpr Vec4 grey = Vec4(' ', 125, 125, 125);
        static constexpr Vec4 white = Vec4(' ', 255, 255, 255);
};

class Vec{
    public:
        static int Length(Vec2<int> pos) {
            return sqrt(pos.x * pos.x + pos.y * pos.y);
        }
        static int Length(int x, int y) {
            return sqrt(x * x + y * y);
        }
        static Vec2<int> Normalize(Vec2<int> v){
            int d = Length(v.x, v.y);
            if (d == 0) { return Vec2<int>::zero; }
            if (v.x == 0) { return Vec2<int>(0, v.y / d); }
            if (v.y == 0) { return Vec2<int>(v.x / d, 0); }
            return Vec2<int>(v.x / d, v.y / d);
        }
        static Vec2<int> Lerp(Vec2<int> a, Vec2<int> b, float t) {
            return a*(1.0f-t) + b*t;
        }
};
