#include "../../include/objects/Polygon.hpp"


Polygon::Polygon(const std::vector<Vector2d>& points, int thickness)
    :maxPoint_(points[0]), minPoint_(points[0]), thickness_(thickness)
{
    for(size_t i = 0; i < points.size(); i++){
        if(i == points.size() - 1)
            lines_.push_back(new Line(points[i], points[0], thickness_));
        else
            lines_.push_back(new Line(points[i], points[i + 1], thickness_));

        if(points[i].x > maxPoint_.x)
            maxPoint_.x = points[i].x;
        if(points[i].y > maxPoint_.y)
            maxPoint_.y = points[i].y;
        if(points[i].x < minPoint_.x)
            minPoint_.x = points[i].x;
        if(points[i].y < minPoint_.y)
            minPoint_.y = points[i].y;
    }
    maxPoint_ += Vector2d(thickness_ / 2, thickness_ / 2);
    minPoint_ -= Vector2d(thickness_ / 2, thickness_ / 2);

    numOfLines_ = lines_.size();
}


bool Polygon::isNear(Ball* ball)
{
    float r = ball->getRadius();
    Vector2d pos = ball->getPos();
    return pos.x <= (maxPoint_.x + r) && pos.y <= (maxPoint_.y + r) && \
           pos.x >= (minPoint_.x - r) && pos.y >= (minPoint_.y - r);
}


void Polygon::Draw(sf::RenderWindow* window)
{
    for(auto line: lines_)
        line->Draw(window);
}


Polygon::~Polygon()
{
    for(auto line: lines_)
        delete line;
}
