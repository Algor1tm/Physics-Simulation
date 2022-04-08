#pragma once

#include "../core/Vector2d.hpp"


class Selectable;
class MovAble;
class RigidBody;
class SoftBody;


class Selectable
{

};


class MovAble
{
public:

	virtual void Move(double time) = 0;
	virtual void Move(const Vector2d& distance) = 0;

	static constexpr float SpeedFactor{ 30.f };
	static constexpr float AccelFactor{ 0.3f };
};