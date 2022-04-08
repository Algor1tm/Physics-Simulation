#include "../../include/objects/RigidBody.hpp"


RigidBody::RigidBody(const Vector2d& startPos, const Vector2d& startSpeed, float mass) :
	Pos{ startPos }, Speed{ startSpeed }, Force{ 0, 0 }, Mass{ mass }
{

}