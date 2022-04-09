#include "../../include/objects/RigidBody.hpp"


RigidBody::RigidBody(const Vector2d& startPos, const Vector2d& startSpeed, float mass) 
    : MovAble(), Selectable(), pos_ {startPos}, speed_{ startSpeed }, force_{ 0, 0 }, mass_{ mass }
{

}


void RigidBody::Move(float time)
{
    speed_ += (MovAble::AccelFactor * time / mass_ * force_);
    pos_ += (MovAble::SpeedFactor * time * speed_);
}


inline void RigidBody::Move(const Vector2d& distance)
{
    pos_ += distance;
}
