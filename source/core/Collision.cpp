#include "../../include/core/Collision.hpp"


bool Collision::CheckCollision(Ball* ball1, Ball* ball2)
{
    float Distance = (ball1->getPos() - ball2->getPos()).getModule();
    return Distance <= ball1->getRadius() + ball2->getRadius();
}


bool Collision::CheckCollision(Ball* ball, Line* line)
{
    Vector2d p1 = line->Point1;
    Vector2d toProject = ball->getPos() - p1;
    Vector2d onProject = line->Point2 - p1;

    float SqauredLength = line->Length * line->Length;

    float project = std::max(0.f, std::min(SqauredLength, Vector2d::DotProduct(toProject, onProject))) / SqauredLength;
    Vector2d ClosestPoint = p1 + project * onProject;

    float Distance = (ball->getPos() - ClosestPoint).getModule();

    return Distance <= ball->getRadius() + line->Thickness / 2;
}


Ball* Collision::CheckCollision(Ball* ball, SoftBody* soft)
{
    Vector2d pos = ball->getPos();
    float r = ball->getRadius();
    Vector2d maxp = soft->getMaxPoint();
    Vector2d minp = soft->getMinPoint();
    if (pos.x <= maxp.x + r && pos.y <= maxp.y + r && pos.x >= minp.x - r && pos.y >= minp.y - r) {
        for (unsigned i = 0; i < soft->getNumOfBalls(); i++) {
            if (CheckCollision(ball, soft->getBall(i)))
                return soft->getBall(i);
        }
    }
    return nullptr;
}


Line* Collision::CheckCollision(Ball* ball, Polygon* polygon)
{
    Line* line;
    for (unsigned i = 0; i < polygon->getSizeofLines(); i++) {
        line = polygon->getLine(i);
        if (CheckCollision(ball, line))
            return line;
    }
    return nullptr;
}


void Collision::Collide(Ball* ball1, Ball* ball2)
{
    Vector2d dpos = ball1->getPos() - ball2->getPos();
    float m = dpos.getModule();

    float Overlap = ball1->getRadius() + ball2->getRadius() - m;
    Vector2d normal = 1 / m * dpos;
    ball1->AddPos(Overlap / 2 * normal);
    ball2->AddPos(-Overlap / 2 * normal);

    Vector2d v1 = ball1->getSpeed();
    Vector2d v2 = ball2->getSpeed();

    float temp = 2 / ((ball1->getMass() + ball2->getMass()) * m * m);

    Vector2d newSpeed;
    newSpeed = -temp * ball2->getMass() * Vector2d::DotProduct(v1 - v2, dpos) * dpos;
    ball1->AddSpeed(newSpeed);

    newSpeed = -temp * ball1->getMass() * Vector2d::DotProduct(v2 - v1, -dpos) * (-dpos);
    ball2->AddSpeed(newSpeed);
}


void Collision::Collide(Ball* ball, Line* line)
{
    float r = ball->getRadius() + line->Thickness / 2;
    Vector2d p1 = line->Point1, p2 = line->Point2;
    Vector2d pos = ball->getPos();
    // edge
    if ((p1 - pos).getModule() <= r) {
        float m = (p1 - pos).getModule();
        float dpos = m - r;
        Vector2d normal = 1 / m * (p1 - pos);
        ball->AddPos(dpos * normal);

        ball->AddSpeed(-EnergyRemainAfterCollision * ball->getSpeed() - ball->getSpeed());
    }
    //edge
    else if ((p2 - pos).getModule() <= r) {
        float m = (p2 - pos).getModule();
        float dpos = m - r;
        Vector2d normal = (p2 - pos) / m;
        ball->AddPos(dpos * normal);

        ball->AddSpeed(-EnergyRemainAfterCollision * ball->getSpeed() - ball->getSpeed());
    }
    //default
    else {
        float dpos = line->Distance(pos) - r;
        if (dpos <= 0) {
            Vector2d normal = line->Normal.getNormalized();
            if (Vector2d::Orientation(p1, p2, pos) != 1)
                normal = -normal;
            ball->AddPos(dpos * normal);

            Vector2d v = ball->getSpeed();
            v = EnergyRemainAfterCollision * Vector2d::Reflect(v, line->Normal);
            ball->AddSpeed(v - ball->getSpeed());
        }
    }
}