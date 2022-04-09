#pragma once

#include "../objects/Objects.hpp"
#include "../objects/Ball.hpp"
#include "../objects/SoftBody.hpp"

#include "Vector2d.hpp"


class SelectManager
{
public:
    SelectManager(sf::RenderWindow* window);
    ~SelectManager() = default;

    void Deselect();
    sf::Event::EventType HandleMousePos(sf::RenderWindow* window, const sf::Event& event);
    void AddObject(Selectable* object) { objects_.push_back(object); }

private:
    std::vector<Selectable*> objects_;

    Selectable* selected_;
    bool rightButton_;
    bool leftButton_;

    static const int SelectParam = 2;

    Selectable* selectObject(const Vector2d& mpos);
    
    void onRightButtonPressed(const Vector2d& mpos) { rightButton_ = true; }
    void onLeftButtonPressed(const Vector2d& mpos) { leftButton_ = true; }

    void onMouseButtonReleased(const Vector2d& mpos) { rightButton_ = leftButton_ = false; }
    void onMouseButtonPressed(const Vector2d& mpos, const sf::Mouse::Button& button);

    void onMouseMoved(const Vector2d& mpos);
};