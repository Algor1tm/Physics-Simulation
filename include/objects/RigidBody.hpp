#pragma once


#include "../core/Vector2d.hpp"


class RigidBody
{
public:
    RigidBody(const Vector2d& startPos, const Vector2d& startSpeed, float mass);
    ~RigidBody() = default;

    Vector2d getSpeed()const { return Speed; }
    Vector2d getPos() const { return Pos; }
    Vector2d getForce() const { return Force; }
    float getMass() const { return Mass; }

    void AddSpeed(const Vector2d& speed) { Speed += speed; }
    void AddPos(const Vector2d& pos) { Pos += pos; }
    void AddForce(const Vector2d& force) { Force += force; }

private:
    Vector2d Pos;
    Vector2d Speed;
    Vector2d Force;
    float Mass;
};