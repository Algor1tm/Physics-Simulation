#include "../../include/core/Engine.hpp"


Engine::Engine(const char* title, const sf::Color& clr)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "AHAHHA", sf::Style::Close, settings);
    Window->setFramerateLimit(FPS);
    bgColor = clr;

    g = {0, 7};

    Pause = 1;
    SelectedBall = nullptr;
    SelectedSoftBody = nullptr;
    RightMouseButton = 0;
    LeftMouseButton = 0;
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

    ApplyGravity(ball);
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
}


void Engine::ApplyGravity(RigidBody* object)
{
    object->AddForce(object->getMass() * g - object->getForce());
}


void Engine::Render()
{
    Window->clear(bgColor);

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


Vector2d Engine::SelectObject(const Vector2d& mpos)
{
    for(unsigned i = 0; i < Balls.size(); i++){
        if((mpos - Balls[i]->getPos()).getModule() <= Balls[i]->getRadius()){
            return {0, (float)i};
        }

    }
    for(unsigned i = 0; i < SoftBodies.size(); i++){
        Vector2d minp = SoftBodies[i]->getMinPoint();
        Vector2d maxp = SoftBodies[i]->getMaxPoint();
        if(mpos.x <= maxp.x && mpos.y <= maxp.y && mpos.x >= minp.x && mpos.y >= minp.y)
            return {1, (float)i};
    }
    return {-1, -1};
}


void Engine::OnMousePressed(const sf::Event& event)
{
    if(Pause)
    {
        Vector2d mpos = {(float)sf::Mouse::getPosition(*Window).x, (float)sf::Mouse::getPosition(*Window).y};
        Vector2d selected = SelectObject(mpos);

        bool isSoftBody = selected.x;
        unsigned index = (int)selected.y;

        if(isSoftBody == 0){
            if(SelectedSoftBody != nullptr){
                SelectedSoftBody->DisableSelectedEfect();
                SelectedSoftBody = nullptr;
            }
            if(SelectedBall == nullptr){
                SelectedBall = Balls[index];
                SelectedBall->EnableSelectedEfect(2);
            }
            else if(SelectedBall != Balls[index] && SelectedBall != nullptr){
                SelectedBall->DisableSelectedEfect();
                SelectedBall = Balls[index];
                SelectedBall->EnableSelectedEfect(2);
            }
            if(event.mouseButton.button == sf::Mouse::Left)
                LeftMouseButton = 1;
            else
                RightMouseButton = 1;
        }
        else if(isSoftBody == 1){
            if(SelectedBall != nullptr){
                SelectedBall->DisableSelectedEfect();
                SelectedBall = nullptr;
            }
            if(SelectedSoftBody == nullptr){
                SelectedSoftBody = SoftBodies[index];
                SelectedSoftBody->EnableSelectedEfect(1);
            }
            else if(SelectedSoftBody != SoftBodies[index] && SelectedSoftBody != nullptr){
                SelectedSoftBody->DisableSelectedEfect();
                SelectedSoftBody = SoftBodies[index];
                SelectedSoftBody->EnableSelectedEfect(1);
            }
            if(event.mouseButton.button == sf::Mouse::Left)
                LeftMouseButton = 1;
            else
                RightMouseButton = 1;
        }
    }
}


void Engine::OnMouseMove(const sf::Event& event)
{
    if(Pause){
        Vector2d mpos = {(float)sf::Mouse::getPosition(*Window).x, (float)sf::Mouse::getPosition(*Window).y};
        if(LeftMouseButton){
            if(SelectedBall != nullptr)
                SelectedBall->Move(mpos - SelectedBall->getPos());
            else if(SelectedSoftBody != nullptr){
                Vector2d center = SelectedSoftBody->getCenter();
                SelectedSoftBody->Move(mpos - center);
            }
        }
        else if(RightMouseButton && SelectedBall != nullptr){
            Vector2d newSpeed = mpos - SelectedBall->getPos();
            SelectedBall->AddSpeed(0.2f * newSpeed - SelectedBall->getSpeed());
        }
    }
}


void Engine::OnKeyPressed(const sf::Event& event)
{
    if(event.key.code == sf::Keyboard::Space){
        if(Pause){
            if(SelectedBall != nullptr){
                SelectedBall->DisableSelectedEfect();
                SelectedBall = nullptr;
            }
            if(SelectedSoftBody != nullptr){
                SelectedSoftBody->DisableSelectedEfect();
                SelectedSoftBody = nullptr;
            }
        }
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
        else if(event.type == sf::Event::MouseMoved){
            OnMouseMove(event);
        }
        else if(event.type == sf::Event::MouseButtonPressed){
            OnMousePressed(event);
        }
        else if(event.type == sf::Event::MouseButtonReleased){
            LeftMouseButton = 0;
            RightMouseButton = 0;
        }
        else if(event.type == sf::Event::KeyPressed){
            OnKeyPressed(event);
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
