#include "../../include/objects/Line.hpp"


float Line::Distance(const Vector2d& point){
    return fabs(a * point.x + b * point.y + c) / NormalModule;

}

Line::Line(const Vector2d& p1, const Vector2d& p2, int LineThickness, const sf::Color& color){
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = p1.x * p2.y - p2.x * p1.y;

    Point1 = p1;
    Point2 = p2;

    Normal = {a, b};
    NormalModule = Normal.getModule();
    Length = (Point2 - Point1).getModule();

    Thickness = LineThickness;
    clr = color;

    Vector2d offset = Thickness / NormalModule * Normal;

    vertices[0].position = {p1.x , p1.y};
    vertices[1].position = {p2.x, p2.y};
    vertices[2].position = {p2.x + offset.x, p2.y + offset.y};
    vertices[3].position = {p1.x + offset.x, p1.y + offset.y};

    for (int i=0; i<4; ++i)
        vertices[i].color = clr;
}

void Line::Draw(sf::RenderWindow* wnd){
    wnd->draw(vertices, 4, sf::Quads);

}
