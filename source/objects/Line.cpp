#include "../../include/objects/Line.hpp"


float Line::Distance(const Vector2d& point)
{
    return fabs(a * point.x + b * point.y + c) / cache_;
}


Line::Line(const Vector2d& p1, const Vector2d& p2, int thickness, const sf::Color& color)
    : a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p2.x * p1.y), point1_(p1), point2_(p2),
    normal_(a, b), thickness_((float)thickness), color_(color)
{
    cache_ = normal_.getLength();
    normal_.normalize();
    length_ = Vector2d::Distance(point1_, point2_);


    Vector2d offset = thickness_ * normal_;
    toDraw_[0].position = {p1.x , p1.y};
    toDraw_[1].position = {p2.x, p2.y};
    toDraw_[2].position = {p2.x + offset.x, p2.y + offset.y};
    toDraw_[3].position = {p1.x + offset.x, p1.y + offset.y};

    for (int i=0; i<4; ++i)
        toDraw_[i].color = color_;
}


void Line::Draw(sf::RenderWindow* window)
{
    window->draw(toDraw_, 4, sf::Quads);
}
