#pragma warning(disable : 26812)

#include "../../include/core/Engine.hpp"


Engine::Engine(const char* title, const sf::Color& clr):
    selector_(Window), backgroundColor(clr), g(0, 7), Pause(1)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "AHAHHA", sf::Style::Close, settings);
    Window->setFramerateLimit(FPS);
}


void Engine::Update(double dt)
{
    if(!Pause){
       for(auto& ball: Balls){
            UpdateBall(ball, dt);
        }

        for(auto& sb: SoftBodies){
            UpdateSoftBody(sb, dt);
        }
    }
}


void Engine::UpdateBall(Ball* ball, double dt)
{
    ApplyCollisions(ball);
    ball->Move(dt);
}


void Engine::UpdateSoftBody(SoftBody* soft, double dt)
{
    ApplyCollisions(soft);
    soft->InnerForces();
    soft->Move(dt);
}


void Engine::ApplyCollisions(SoftBody* soft)
{
    Ball* ball;
    Ball* otherball;
    unsigned num = soft->getNumOfBalls();

    for (unsigned j = 0; j < num; j++) {
        ball = soft->getBall(j);

        for (auto& target : SoftBodies) {
            if (target != soft) {
                otherball = Collision::CheckCollision(ball, target);
                if (otherball != nullptr)
                    Collision::Collide(ball, otherball);
            }
        }
        ApplyCollisions(ball);

        ApplyGravity(ball);
    }
}


void Engine::ApplyCollisions(Ball* ball)
{
    for(auto& target: Balls){
        if(ball != target){
            if(Collision::CheckCollision(ball, target))
                Collision::Collide(ball, target);
        }
    }
    Line* line;
    for(auto& pol: Polygons){
        if(pol->isNear(ball)){
            line = Collision::CheckCollision(ball, pol);
            if(line != nullptr)
                Collision::Collide(ball, line);
        }
    }
    for(auto& line: Lines){
        if(Collision::CheckCollision(ball, line))
            Collision::Collide(ball, line);
    }

    ApplyGravity(ball);
}


void Engine::ApplyGravity(RigidBody* object)
{
    object->AddForce(object->getMass() * g - object->getForce());
}


void Engine::Render()
{
    Window->clear(backgroundColor);

    for(auto& object: Lines){
        object->Draw(Window);
    }

    for(auto& object: Polygons){
        object->Draw(Window);
    }

    for(auto& object: Balls){
        object->Draw(Window);
    }

    for(auto& object: SoftBodies){
        object->Draw(Window);
    }

    Window->display();
}


void Engine::OnKeyPressed(const sf::Keyboard::Key& keycode)
{
    if(keycode == sf::Keyboard::Space){
        if(Pause)
            selector_.Deselect();

        Pause = !Pause;
    }
}


int Engine::HandleEvents()
{
    sf::Event event;

    while (Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            return 1;
        }
        else if (event.type == sf::Event::KeyPressed) {
            OnKeyPressed(event.key.code);
        }

        else if (Pause)
        {
            selector_.HandleMousePos(Window, event);
        }
    }
    return 0;
}


Engine::~Engine()
{
    for(auto& object: Balls){
        delete object;
    }
    for(auto& object: Lines){
        delete object;
    }
    for(auto& object: Polygons){
        delete object;
    }
    for(auto& object: SoftBodies){
        delete object;
    }

    delete Window;
}
