#pragma once

#include "../core/Vector2d.hpp"


class Selectable;
class MovAble;
class RigidBody;
class SoftBody;


class Selectable
{
protected:
	bool selected_;

public:
	Selectable(): selected_(false) {}

	virtual bool isInside(const Vector2d& pos) = 0;

	virtual void OnLeftMouseMove(const Vector2d& mousePos) = 0;
	virtual void OnRightMouseMove(const Vector2d& mousePos) = 0;

	virtual void OnSelect(int param) = 0;
	virtual void OnDeselect(int param) = 0;
};


class MovAble
{
public:
	virtual void Move(double time) = 0;
	virtual void Move(const Vector2d& distance) = 0;

	static constexpr float SpeedFactor = 30.f;
	static constexpr float AccelFactor = 0.3f;
};
