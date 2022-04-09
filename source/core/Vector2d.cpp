#include "../../include/core/Vector2d.hpp"


Vector2d Vector2d::Reflect(const Vector2d& ToReflect, const Vector2d& v)
{
    Vector2d res = ToReflect;
    float m = v.getLength();
    float temp = Vector2d::DotProduct(res, v) / (m * m);
    res -= 2 * temp * v;
    return res;
}


int Vector2d::Orientation(const Vector2d& p, const Vector2d& q, const Vector2d& r)
{
    float val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counter clock wise
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
    float m = getLength();
    x /= m, y /= m;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Vector2d& v)
{
    os << "Vector2d(" << v.x << ", " << v.y << ')' << std::endl;
    return os;
}
