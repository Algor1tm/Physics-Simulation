#pragma once 

#include "SFML/Graphics.hpp"

#include "../core/Vector2d.hpp"
#include "Objects.hpp"


class RigidBody: public MovAble, public Selectable
{
public:
    RigidBody(const Vector2d& startPos, const Vector2d& startSpeed, float mass);
    ~RigidBody() = default;

    virtual void Draw(sf::RenderWindow* window) = 0;

    virtual void Move(float time) override;
    virtual void Move(const Vector2d& distance) override;

    Vector2d getSpeed() const  { return speed_; }
    Vector2d getPos()   const  { return pos_;   }
    Vector2d getForce() const  { return force_; }
    float    getMass()  const  { return mass_;  }

    void AddSpeed(const Vector2d& speed) { speed_ += speed; }
    void AddPos(const Vector2d& pos)     { pos_ += pos;     }
    void AddForce(const Vector2d& force) { force_ += force; }

private:
    Vector2d pos_;
    Vector2d speed_;
    Vector2d force_;
    float mass_;
};