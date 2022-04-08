#pragma warning(disable : 26812)

#include "../../include/core/SelectManager.hpp"


SelectManager::SelectManager(sf::RenderWindow* window):
	selected_(nullptr), rightButton_(false), leftButton_(false)
{

}


void SelectManager::Deselect()
{
    if (selected_ != nullptr) {
        selected_->OnDeselect(SelectParam);

        selected_ = nullptr;
        rightButton_ = false;
        leftButton_ = false;
    }
}


Selectable* SelectManager::SelectObject(const Vector2d& mpos)
{
    for (auto& object : objects_){
        if (object->isInside(mpos))
            return object;
    }
    return nullptr;
}


void SelectManager::OnMouseButtonPressed(const Vector2d& mpos, const sf::Mouse::Button& button)
{
    Selectable* candidate = SelectObject(mpos);

    if (candidate != nullptr) {
        if (selected_ != candidate || selected_ == nullptr) {
            if (selected_ != nullptr)
                selected_->OnDeselect(SelectParam);
            selected_ = candidate;
            selected_->OnSelect(SelectParam);
        }
        if (button == sf::Mouse::Right)
            OnRightButtonPressed(mpos);
        else if (button == sf::Mouse::Left)
            OnLeftButtonPressed(mpos);
    }
}


void SelectManager::OnMouseMoved(const Vector2d& mpos)
{
    if (selected_ != nullptr) {
        if (rightButton_)
            selected_->OnRightMouseMove(mpos);
        else if (leftButton_)
            selected_->OnLeftMouseMove(mpos);
    }
}


sf::Event::EventType SelectManager::HandleMousePos(sf::RenderWindow* window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved) {
        Vector2d mpos = sf::Mouse::getPosition(*window);
        OnMouseMoved(mpos);
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        Vector2d mpos = sf::Mouse::getPosition(*window);
        OnMouseButtonReleased(mpos);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        Vector2d mpos = sf::Mouse::getPosition(*window);
        OnMouseButtonPressed(mpos, event.mouseButton.button);
    }

    return event.type;
}