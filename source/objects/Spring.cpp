#include "../../include/objects/SoftBody.hpp"


SoftBody::Spring::Spring(Ball* ball1, Ball* ball2)
    : ball1_(ball1), ball2_(ball2), cache_(ball1_->getRadius() + ball2_->getRadius())
{
    defaultVector_ = ball1->getPos() - ball2->getPos();
    defaultLength_ = defaultVector_.getLength();
}


void SoftBody::Spring::ApplySelfCollision()
{
    Vector2d dpos = ball1_->getPos() - ball2_->getPos();

    float distance = dpos.getLength();
    if (cache_ >= distance + 1 && distance != 0)
    {
        dpos = dpos / (2 * distance);
        ball1_->AddPos(dpos);
        ball2_->AddPos(-dpos);
    }
}


void SoftBody::Spring::ApplyDampingFactor()
{
    Vector2d dpos = ball2_->getPos() - ball1_->getPos();
    dpos.normalize();

    Vector2d dspeed = ball2_->getSpeed() - ball1_->getSpeed();
    float D = Spring::Kd * Vector2d::DotProduct(dspeed, dpos);
    Vector2d Damping = D * dpos;

    ball1_->AddForce(Damping);
    ball2_->AddForce(-Damping);
}


void SoftBody::Spring::ApplyHookesForce()
{
    Vector2d dpos = ball1_->getPos() - ball2_->getPos();
    float distance = dpos.getLength();
    float dx = distance - defaultLength_;

    Vector2d F = Spring::Ks * dx / distance * dpos;

    ball1_->AddForce(-F);
    ball2_->AddForce(F);
}


void SoftBody::Spring::Draw(sf::RenderWindow* window)
{
    sf::Vertex line[] = {
        sf::Vertex({ ball1_->getPos().x, ball1_->getPos().y }),
        sf::Vertex({ ball2_->getPos().x, ball2_->getPos().y })
    };
    window->draw(line, 2, sf::Lines);
}


