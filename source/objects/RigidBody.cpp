#include "../../include/objects/RigidBody.hpp"


RigidBody::RigidBody(const Vector2d& startPos, const Vector2d& startSpeed, float mass) :
    MovAble(), pos_ {startPos}, speed_{ startSpeed }, force_{ 0, 0 }, mass_{ mass }
{

}


void RigidBody::Move(double time)
{
    speed_ += (MovAble::AccelFactor * time / mass_ * force_);
    pos_ += (MovAble::SpeedFactor * time * speed_);
}


void RigidBody::Move(const Vector2d& distance)
{
    pos_ += distance;
}