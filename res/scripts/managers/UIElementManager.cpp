#include "UIElementManager.h"

//Static class variable initialization.
forward_list<UIElement*> UIElementManager::elements;
RenderWindow* UIElementManager::window;

UIElementManager::UIElementManager(RenderWindow* window){
    //If the UI Element Manager is created without a valid renderwindow pointer, throw an exception.
    if (window == nullptr){
        throw invalid_argument("UIElementManager initialized without a valid renderwindow pointer!");
    }

    UIElementManager::window = window;
}

bool UIElementManager::addElement(UIElement* element){
    //1. Check if the elements already exists, if not, add it.
    for (const UIElement* i : elements){
        if (i == element){
            return false;
        }
    }
    elements.push_front(element);
    return true;
}

void UIElementManager::drawAllElements(){
    for (UIElement* i : elements){
        window->draw((i->getSprite()));
    }
}

void UIElementManager::activateElement(const Vector2i &mouseLocation){
    //1. Check if the mouse location is within the bounds of any elements.
    for (UIElement* i : elements){
        if (i->getSprite().getGlobalBounds().contains(Vector2f(mouseLocation))){
            i->callFunction();
            break;
        }
    }
}