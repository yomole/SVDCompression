#include "UIElementManager.h"

//Static class variable initialization.
forward_list<SpriteBased*> UIElementManager::elements;
forward_list<TextBased*> UIElementManager::text;
RenderWindow* UIElementManager::window;

UIElementManager::UIElementManager(RenderWindow* window){
    //If the UI Element Manager is created without a valid renderwindow pointer, throw an exception.
    if (window == nullptr){
        throw invalid_argument("UIElementManager initialized without a valid renderwindow pointer!");
    }

    UIElementManager::window = window;
}

bool UIElementManager::addElement(SpriteBased* element){
    //1. Check if the elements already exists, if not, add it.
    for (const SpriteBased* i : elements){
        if (i == element){
            return false;
        }
    }

    elements.push_front(element);
    return true;
}

bool UIElementManager::addElement(TextBased* element){
    //1. Check if the elements already exists, if not, add it.
    for (const TextBased* i : text){
        if (i == element){
            return false;
        }
    }

    text.push_front(element);
    return true;
}

void UIElementManager::drawAll(){
    //1. Draw all sprite based elements.
    for (SpriteBased* i : elements){
        window->draw(i->getSprite());
    }

    //2. Draw all text based elements.
    for (TextBased* i : text){
        window->draw(i->text);
    }
}

void UIElementManager::activateElement(const Vector2i &mouseLocation){
    //1. Check if the mouse location is within the bounds of any elements.
    for (SpriteBased* i : elements){
        if (i->getSprite().getGlobalBounds().contains(Vector2f(mouseLocation))){
            i->callFunction();
            break;
        }
    }
}