#pragma once

#include <math.h>
#include <ostream>

#include <SFML/System/Vector2.hpp>


struct Vector2d{
    float x;
    float y;

    Vector2d(){x = 0, y = 0;}
    Vector2d(float X, float Y) { x = X, y = Y;}
    Vector2d(const Vector2d& v) {x = v.x, y = v.y;}
    Vector2d(const sf::Vector2f& v) { x = v.x, y = v.y; }
    Vector2d(const sf::Vector2i& v) { x = (float)v.x, y = (float)v.y; }

    float getModule() const {return std::sqrt(x * x + y * y);}
    Vector2d getNormalized() const;
    Vector2d& normalize();

    operator sf::Vector2f() const {return sf::Vector2f(x, y);}

    Vector2d& operator+=(const Vector2d& v);
    Vector2d& operator-=(const Vector2d& v);

    friend Vector2d operator*(float k, const Vector2d& v){return Vector2d(v.x * k, v.y * k); }
    friend Vector2d operator*(const Vector2d& v, float k) { return Vector2d(v.x * k, v.y * k); }
    friend Vector2d operator/(const Vector2d& v, float k) { return Vector2d{v.x / k, v.y / k}; }
    friend Vector2d operator-(const Vector2d& v){return Vector2d(-v.x, -v.y);}

    friend Vector2d operator+(const Vector2d& v1, const Vector2d& v2){return Vector2d(v1.x + v2.x, v1.y + v2.y);}
    friend Vector2d operator-(const Vector2d& v1, const Vector2d& v2){return Vector2d(v1.x - v2.x, v1.y - v2.y);}

    friend bool operator ==(const Vector2d& v1, const Vector2d& v2) {return (v1.x == v2.x) && (v1.y == v2.y);}

    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v);

    static float DotProduct(const Vector2d& v1, const Vector2d& v2) {return v1.x * v2.x + v1.y * v2.y;}
    static Vector2d Reflect(const Vector2d& ToReflect, const Vector2d& v);
    static float Distance(const Vector2d& v1, const Vector2d& v2) { return (v1 - v2).getModule(); }
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    static int Orientation(const Vector2d& p, const Vector2d& q, const Vector2d& r);
};

