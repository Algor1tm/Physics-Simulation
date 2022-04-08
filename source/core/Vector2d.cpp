#include "../../include/core/Vector2d.hpp"


Vector2d Vector2d::Reflect(const Vector2d& ToReflect, const Vector2d& v)
{
    Vector2d res = ToReflect;
    float m = v.getModule();
    float temp = Vector2d::DotProduct(res, v) / (m * m);
    res -= 2 * temp * v;
    return res;
}

Vector2d Vector2d::getNormalized() const
{
    Vector2d v{ x, y };
    v.normalize();
    return v;
}

Vector2d& Vector2d::operator+=(const Vector2d& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2d& Vector2d::normalize()
{
    float m = getModule();
    x /= m, y /= m;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2d& v)
{
    os << "Vector2d(" << v.x << ", " << v.y << ')' << std::endl;
    return os;
}
