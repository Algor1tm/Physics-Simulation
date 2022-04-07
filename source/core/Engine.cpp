#include "../../include/core/Engine.hpp"


Engine::Engine(const char* title, const sf::Color& clr){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "AHAHHA", sf::Style::Close, settings);
    Window->setFramerateLimit(FPS);
    bgColor = clr;

    Speedfactor = 30.f;
    Accelfactor = 0.3f;
    g = {0, 7};
    EnergyRemainAfterCollision = 0.95f;

    Pause = 1;
    SelectedBall = nullptr;
    SelectedSoftBody = nullptr;
    RightMouseButton = 0;
    LeftMouseButton = 0;
}


void Engine::Update(double dt){
    if(!Pause){
       for(auto& ball: Balls){
        UpdateBall(ball, dt);
        }

        for(auto& sb: SoftBodies){
            UpdateSoftBody(sb, dt);
        }
    }
}


void Engine::UpdateBall(Ball* ball, double dt){
    ApplyCollisions(ball, 0);

    ForceObject(ball);
    MoveObject(ball, dt);
}


void Engine::UpdateSoftBody(SoftBody* sb, double dt){
    Ball* ball;
    Ball* otherball;
    unsigned num = sb->getNumOfBalls();

    for(unsigned j = 0; j < num; j++){
        ball = sb->getBall(j);

        for(auto& target: SoftBodies){
            if(target != sb){
                otherball = CheckCollision(ball, target);
                if(otherball != nullptr)
                    Collide(ball, otherball);
            }
        }

        ApplyCollisions(ball, 1);
        ForceObject(ball);
    }

    sb->InnerForces();

    for(unsigned j = 0; j < num; j++){
        ball = sb->getBall(j);
        MoveObject(ball, dt);
    }
}


void Engine::ApplyCollisions(Ball* ball, bool softBody){
    for(auto& target: Balls){
        if(ball != target){
            if(CheckCollision(ball, target))
                Collide(ball, target);
        }
    }

    Line* line;
    for(auto& pol: Polygons){
        if(pol->isNear(ball)){
            line = CheckCollision(ball, pol);
            if(line != nullptr)
                Collide(ball, line, softBody);
        }
    }
    for(auto& line: Lines){
        if(CheckCollision(ball, line))
            Collide(ball, line, softBody);
        }
}


Ball* Engine::CheckCollision(Ball* ball, SoftBody* body){
    Vector2d pos = ball->getPos();
    float r = ball->getRadius();
    Vector2d maxp = body->getMaxPoint();
    Vector2d minp = body->getMinPoint();
    if(pos.x <= maxp.x + r && pos.y <= maxp.y + r && pos.x >= minp.x - r && pos.y >= minp.y - r){
        for(unsigned i = 0; i < body->getNumOfBalls(); i++){
            if(CheckCollision(ball, body->getBall(i)))
                return body->getBall(i);
        }
    }
    return nullptr;
}

Line* Engine::CheckCollision(Ball* ball, Polygon* pol){
    Line* line;
    for(unsigned i = 0; i < pol->getSizeofLines(); i++){
        line = pol->getLine(i);
        if(CheckCollision(ball, line))
            return line;
    }
    return nullptr;
}


void Engine::Collide(Ball* ball1, Ball* ball2){
    Vector2d dpos = ball1->getPos() - ball2->getPos();
    float m = dpos.getModule();

    float Overlap = ball1->getRadius() + ball2->getRadius() - m;
    Vector2d normal = 1 / m * dpos;
    ball1->setPos(ball1->getPos() + Overlap / 2 * normal);
    ball2->setPos(ball2->getPos() - Overlap / 2 * normal);

    Vector2d v1 = ball1->getSpeed();
    Vector2d v2 = ball2->getSpeed();

    float temp = 2 /((ball1->getMass() + ball2->getMass()) * m * m);

    Vector2d newSpeed = v1;
    newSpeed -= temp * ball2->getMass() * Vector2d::DotProduct(v1 - v2, dpos) * dpos;
    ball1->setSpeed(newSpeed);


    newSpeed = v2;
    newSpeed -= temp * ball1->getMass() * Vector2d::DotProduct(v2 - v1, -dpos) * (-dpos);
    ball2->setSpeed(newSpeed);
}


bool Engine::CheckCollision(Ball* ball1, Ball* ball2){
    float Distance = (ball1->getPos() - ball2->getPos()).getModule();

    return Distance <= ball1->getRadius() + ball2->getRadius();
}


void Engine::Collide(Ball* ball, Line* line, bool softBody){
    float r = ball->getRadius() + line->Thickness / 2;
    Vector2d p1 = line->Point1, p2 = line->Point2;
    Vector2d pos = ball->getPos();
    if((p1 -  pos).getModule() <= r && !softBody){
        float m = (p1 -  pos).getModule();
        float dpos = m - r;
        Vector2d normal = 1 / m * (p1 - pos);
        ball->setPos(pos + dpos * normal);

	    ball->setSpeed(-EnergyRemainAfterCollision * ball->getSpeed());
    }
	else if ((p2 - pos).getModule() <= r && !softBody) {
		float m = (p2 - pos).getModule();
		float dpos = m - r;
		Vector2d normal = 1 / m * (p2 - pos);
		ball->setPos(pos + dpos * normal);

        ball->setSpeed( -EnergyRemainAfterCollision * ball->getSpeed() );
    }
    else{
        float dpos = line->Distance(pos) - r;
        if (dpos <= 0) {
			Vector2d normal = 1 / line->NormalModule * line->Normal;
			if (orientation(p1, p2, pos) != 1)
				normal = -normal;
			ball->setPos(pos + dpos * normal);

			Vector2d v = ball->getSpeed();
			v = EnergyRemainAfterCollision * Vector2d::Reflect(v, line->Normal);
			ball->setSpeed(v);
        }
    }
}


bool Engine::CheckCollision(Ball* ball, Line* line){
    Vector2d p1 = line->Point1;
    Vector2d toProject = ball->getPos() - p1;
    Vector2d onProject = line->Point2 - p1;

    float SqauredLength = line->Length * line->Length;

    float project = std::max(0.f, std::min(SqauredLength, Vector2d::DotProduct(toProject, onProject))) / SqauredLength;
    Vector2d ClosestPoint = p1 + project * onProject;

    float Distance = (ball->getPos() - ClosestPoint).getModule();

    return Distance <=  ball->getRadius() + line->Thickness / 2;
}

void Engine::MoveObject(Ball* ball, Vector2d dx){
    ball->setPos(ball->getPos() + dx);
}

void Engine::MoveObject(Ball* object, double dt){
    object->setSpeed(object->getSpeed() + Accelfactor * dt / object->getMass() * object->getForce());
    object->setPos(object->getPos() + Speedfactor * dt * object->getSpeed());
}


void Engine::ForceObject(Ball* object){
    object->setForce(object->getMass() * g);
}


int Engine::orientation(const Vector2d& p, const Vector2d& q, const Vector2d& r){
    float val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear
    return (val > 0)? 1: 2; // clock or counter clock wise
}


void Engine::Render(){
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

Vector2d Engine::SelectObject(const Vector2d& mpos){
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


void Engine::OnMousePressed(const sf::Event& event){
    if(Pause){
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

void Engine::OnMouseMove(const sf::Event& event){
    if(Pause){
        Vector2d mpos = {(float)sf::Mouse::getPosition(*Window).x, (float)sf::Mouse::getPosition(*Window).y};
        if(LeftMouseButton){
            if(SelectedBall != nullptr)
                MoveObject(SelectedBall, mpos - SelectedBall->getPos());
            else if(SelectedSoftBody != nullptr){
                Vector2d center = SelectedSoftBody->getCenter();
                for(unsigned i = 0; i < SelectedSoftBody->getNumOfBalls(); i++)
                    MoveObject(SelectedSoftBody->getBall(i), mpos - center);
            }
        }
        else if(RightMouseButton && SelectedBall != nullptr){
            Vector2d newSpeed = mpos - SelectedBall->getPos();
            SelectedBall->setSpeed(0.2f * newSpeed);

        }
    }
}

void Engine::OnKeyPressed(const sf::Event& event){
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

int Engine::HandleEvents(){
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

Engine::~Engine(){
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
