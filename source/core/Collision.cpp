#include "../../include/core/Collision.hpp"


bool Collision::CheckCollision(Ball* ball1, Ball* ball2)
{
    return Vector2d::Distance(ball1->getPos(), ball2->getPos()) <= ball1->getRadius() + ball2->getRadius();
}


bool Collision::CheckCollision(Ball* ball, Line* line)
{
    Vector2d p1 = line->getPoint1();
    Vector2d toProject = ball->getPos() - p1;
    Vector2d surface = line->getPoint2() - p1;

    float sqauredLength = line->getLength() * line->getLength();

    float project = std::max(0.f, std::min(sqauredLength, Vector2d::DotProduct(toProject, surface))) / sqauredLength;
    Vector2d closestPoint = p1 + project * surface;

    float distance = Vector2d::Distance(ball->getPos(), closestPoint);

    return distance <= ball->getRadius() + line->getThickness() / 2;
}


Ball* Collision::CheckCollision(Ball* ball, SoftBody* soft)
{
    if (soft->isNear(ball)) {
        Ball* candidate;
        for (size_t i = 0; i < soft->getNumOfBalls(); i++) {
            candidate = soft->getBall(i);
            if (CheckCollision(ball, candidate))
                return candidate;
        }
    }
    return nullptr;
}


Line* Collision::CheckCollision(Ball* ball, Polygon* polygon)
{
    if (polygon->isNear(ball)) {
        Line* candidate;
        for (size_t i = 0; i < polygon->getNumofLines(); i++) {
            candidate = polygon->getLine(i);
            if (CheckCollision(ball, candidate))
                return candidate;
        }
    }
    return nullptr;
}


void Collision::Collide(Ball* ball1, Ball* ball2)
{
    Vector2d dpos = ball1->getPos() - ball2->getPos();
    float distance = dpos.getLength();

    float Overlap = ball1->getRadius() + ball2->getRadius() - distance;
    Vector2d normalized = dpos / distance;
    ball1->AddPos(Overlap / 2 * normalized);
    ball2->AddPos(-Overlap / 2 * normalized);

    Vector2d v1 = ball1->getSpeed();
    Vector2d v2 = ball2->getSpeed();

    float temp = 2 / ((ball1->getMass() + ball2->getMass()) * distance * distance);

    Vector2d newSpeed;
    newSpeed = -temp * ball2->getMass() * Vector2d::DotProduct(v1 - v2, dpos) * dpos;
    ball1->AddSpeed(newSpeed);

    newSpeed = temp * ball1->getMass() * Vector2d::DotProduct(v2 - v1, -dpos) * dpos;
    ball2->AddSpeed(newSpeed);
}


void Collision::Collide(Ball* ball, Line* line)
{
    float max = ball->getRadius() + line->getThickness() / 2;

    Vector2d pos = ball->getPos();
    Vector2d point1 = line->getPoint1();
    Vector2d point2 = line->getPoint2();
    float distToEdge1 = Vector2d::Distance(point1, pos);
    float distToEdge2 = Vector2d::Distance(point2, pos);
    // edge
    if (distToEdge1 <= max)
    {
        float dpos = distToEdge1 - max;
        Vector2d normalized = (point1 - pos) / distToEdge1;
        ball->AddPos(dpos * normalized);

        ball->AddSpeed(-EnergyRemainAfterCollision * ball->getSpeed() - ball->getSpeed());
    }
    //edge
    else if (distToEdge2 <= max)
    {
        float dpos = distToEdge2 - max;
        Vector2d normalized = (point2 - pos) / distToEdge2;
        ball->AddPos(dpos * normalized);

        ball->AddSpeed(-EnergyRemainAfterCollision * ball->getSpeed() - ball->getSpeed());
    }
    //default
    else 
    {
        float dpos = line->Distance(pos) - max;
        Vector2d normal = line->getNormal();
        if (Vector2d::Orientation(point1, point2, pos) != 1)
            normal = -normal;
        ball->AddPos(dpos * normal);

        Vector2d v = ball->getSpeed();
        v = EnergyRemainAfterCollision * Vector2d::Reflect(v, normal);
        ball->AddSpeed(v - ball->getSpeed());
    }
}
