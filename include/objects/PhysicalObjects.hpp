#pragma once

#include <SFML/Graphics.hpp>


class DrawAble{
public:
    virtual ~DrawAble() = default;

    virtual void Draw(sf::RenderWindow* wnd)= 0;
};

class MovAble{
public:
    virtual ~MovAble() = default;
};

class Static{
public:
    virtual ~Static() = default;
};
