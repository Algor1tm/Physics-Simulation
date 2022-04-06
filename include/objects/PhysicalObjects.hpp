#ifndef PHYSICALOBJECT_HPP_INCLUDED
#define PHYSICALOBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>


class DrawAble{
public:
    virtual ~DrawAble() {}
    virtual void Draw(sf::RenderWindow* wnd)= 0;

};

class MovAble{
public:
    virtual ~MovAble() {}

};

class Static{
public:
    virtual ~Static() {;}

};

#endif // PHYSICALOBJECT_HPP_INCLUDED
