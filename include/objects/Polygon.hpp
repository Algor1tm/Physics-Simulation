#pragma once

#include <SFML/Graphics.hpp>

#include "../core/Vector2d.hpp"
#include "Line.hpp"
#include "Ball.hpp"


class Polygon{
public:
    // declare points only in CLOCKWISE order
    Polygon(const std::vector<Vector2d>& points, float thickness);
    ~Polygon();

    void Draw(sf::RenderWindow* window);

    bool isNear(Ball* ball);

    Line* getLine(int i) const {return lines_[i];}
    size_t getNumofLines() const {return numOfLines_;}

private:
    std::vector<Line*> lines_;
    size_t numOfLines_;

    Vector2d maxPoint_;
    Vector2d minPoint_;

    float thickness_;
};

