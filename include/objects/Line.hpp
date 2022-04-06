#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

#include "PhysicalObjects.hpp"
#include "../core/Vector2d.hpp"


// ax + by + c = 0;
struct Line: public Static, public DrawAble{
    float a;
    float b;
    float c;

    Vector2d Normal;
    float NormalModule;
    float Length;

    Vector2d Point1;
    Vector2d Point2;

    sf::Vertex vertices[4];
    sf::Color clr;
    int Thickness;


    Line(const Vector2d& p1, const Vector2d& p2, int LineThickness, const sf::Color& color = sf::Color::White);
    virtual ~Line() {;}

    float Distance(const Vector2d& point);
    void Draw(sf::RenderWindow* wnd)override;
};

#endif // LINE_HPP_INCLUDED
