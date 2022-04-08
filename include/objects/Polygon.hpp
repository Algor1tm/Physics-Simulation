#pragma once

#include <SFML/Graphics.hpp>

#include "../core/Vector2d.hpp"
#include "Line.hpp"
#include "Ball.hpp"


class Polygon{
private:
    std::vector<Line*> lines;

    Vector2d MaxPoint;
    Vector2d MinPoint;

    int OutLineThickness;

public:
    // declare points only in CLOCKWISE order
    Polygon(std::vector<Vector2d> points, int Thickness);
    virtual ~Polygon();

    void Draw(sf::RenderWindow* wnd);

    bool isNear(Ball* ball);

    Line* getLine(int i){return lines[i];}
    unsigned getSizeofLines() {return lines.size();}
};

