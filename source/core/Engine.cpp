#include "../../include/core/Engine.hpp"


Engine::Engine(const std::string& title, const sf::Color& color)
    : selector_(window_), backgroundColor_(color), gravity(0, 7), pause_(true), running_(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window_ = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), title, sf::Style::Close, settings);
    window_->setFramerateLimit(FPS);
}


void Engine::Update(float elapsedTime)
{
    if(pause_ == false)
    {
        for(auto& ball: balls_)
            updateBall(ball, elapsedTime);

        for(auto& soft: softBodies_)
            updateSoftBody(soft, elapsedTime);
    }
}


void Engine::updateBall(Ball* ball, float elapsedTime)
{
    applyCollisions(ball);
    ball->Move(elapsedTime);
}


void Engine::updateSoftBody(SoftBody* soft, float elapsedTime)
{
    applyCollisions(soft);
    soft->InnerForces();
    soft->Move(elapsedTime);
}


void Engine::applyCollisions(SoftBody* soft)
{
    Ball* ball;
    Ball* otherball;
    size_t num = soft->getNumOfBalls();

    for (size_t i = 0; i < num; i++) 
    {
        ball = soft->getBall(i);
        for (auto& othersoft : softBodies_) 
        {
            if (othersoft != soft)
            {
                otherball = Collision::CheckCollision(ball, othersoft);
                if (otherball != nullptr)
                    Collision::Collide(ball, otherball);
            }
        }
        applyCollisions(ball);

        applyGravity(ball);
    }
}


void Engine::applyCollisions(Ball* ball)
{
    for(auto& target: balls_)
    {
        if(ball != target)
        {
            if(Collision::CheckCollision(ball, target))
                Collision::Collide(ball, target);
        }
    }

    Line* line;
    for(auto& pol: polygons_)
    {
        line = Collision::CheckCollision(ball, pol);
        if(line != nullptr)
            Collision::Collide(ball, line);
    }

    for(auto& line: lines_)
    {
        if(Collision::CheckCollision(ball, line))
            Collision::Collide(ball, line);
    }

    applyGravity(ball);
}


void Engine::applyGravity(RigidBody* object)
{
    object->AddForce(object->getMass() * gravity - object->getForce());
}


void Engine::Render()
{
    window_->clear(backgroundColor_);

    for(auto& line: lines_)
        line->Draw(window_);

    for(auto& polygon: polygons_)
        polygon->Draw(window_);

    for (auto& ball : balls_)
        ball->Draw(window_);

    for(auto& soft: softBodies_)
        soft->Draw(window_);
    window_->display();
}


void Engine::onKeyPressed(const sf::Keyboard::Key& keycode)
{
    if(keycode == sf::Keyboard::Space)
    {
        if(pause_ == true)
            selector_.Deselect();

        pause_ = !pause_;
    }
}


void Engine::HandleEvents()
{
    sf::Event event;

    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            running_ = false;

        else if (event.type == sf::Event::KeyPressed)
            onKeyPressed(event.key.code);

        else if (pause_)
            selector_.HandleMousePos(window_, event);
    }
}


Engine::~Engine()
{
    for(auto& ball: balls_)
        delete ball;

    for(auto& line: lines_)
        delete line;

    for(auto& polygon : polygons_)
        delete polygon;

    for(auto& soft: softBodies_)
        delete soft;

    delete window_;
}
