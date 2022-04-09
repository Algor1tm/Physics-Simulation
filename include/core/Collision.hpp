#pragma once

#include "Vector2d.hpp"

#include "../objects/Ball.hpp"
#include "../objects/SoftBody.hpp"
#include "../objects/Line.hpp"
#include "../objects/Polygon.hpp"


class Collision
{
public:
	Collision() = delete;

	static bool CheckCollision(Ball* ball1, Ball* ball2);
	static bool CheckCollision(Ball* ball, Line* line);

	static Ball* CheckCollision(Ball* ball, SoftBody* soft);
	static Line* CheckCollision(Ball* ball, Polygon* polygon);

	static void Collide(Ball* ball1, Ball* ball2);
	static void Collide(Ball* ball, Line* line);
	
	static constexpr float EnergyRemainAfterCollision = 0.95f;
};
