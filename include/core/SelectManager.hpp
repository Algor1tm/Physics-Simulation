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

    Selectable* SelectObject(const Vector2d& mpos);
    
    void OnRightButtonPressed(const Vector2d& mpos) { rightButton_ = true; }
    void OnLeftButtonPressed(const Vector2d& mpos) { leftButton_ = true; }

    void OnMouseButtonReleased(const Vector2d& mpos) { rightButton_ = leftButton_ = false; }
    void OnMouseButtonPressed(const Vector2d& mpos, const sf::Mouse::Button& button);

    void OnMouseMoved(const Vector2d& mpos);
};