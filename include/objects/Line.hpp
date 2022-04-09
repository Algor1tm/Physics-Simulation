#pragma once

#include "SFML/Graphics.hpp"

#include "../core/Vector2d.hpp"


// ax + by + c = 0;
class Line{
public:
    Line(const Vector2d& point1, const Vector2d& point2, float thickness, const sf::Color& color = sf::Color::White);
    virtual ~Line() = default;

    float Distance(const Vector2d& point);
    void Draw(sf::RenderWindow* window);

    Vector2d getPoint1() const { return point1_; }
    Vector2d getPoint2() const { return point2_; }
    Vector2d getNormal() const { return normal_; }
    float getLength() const { return length_; }
    float getThickness() const { return thickness_; }

private:
    float a;
    float b;
    float c;

    Vector2d point1_;
    Vector2d point2_;

    // normalized
    Vector2d normal_;
    float length_;
    float thickness_;

    sf::Vertex toDraw_[4];
    sf::Color color_;

    // sqrt(a*a + b*b)
    float cache_;
};

