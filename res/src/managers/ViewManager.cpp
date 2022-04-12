#include "ViewManager.h"

//Static class variable initialization.
RenderWindow* ViewManager::window;
unordered_map<string, View> ViewManager::views;
View* ViewManager::currentView;

ViewManager::ViewManager(RenderWindow* window){
    //If the UI Element Manager is created without a valid renderwindow pointer, throw an exception.
    if (window == nullptr){
        throw invalid_argument("ViewManager initialized without a valid renderwindow pointer!");
    }

    ViewManager::window = window;
    ViewManager::currentView = nullptr;
}

bool ViewManager::addView(const string &viewName, const string &viewFile){
    if (views.count(viewName) == 0) {
        views.insert(pair<string, View>(viewName, View(viewFile)));
        return true;
    }
    else{
        return false;
    }
}

bool ViewManager::changeView(const string &viewName){
    if (views.count(viewName) != 0){
        currentView = &(views.at(viewName));
        return true;
    }
    else{
        return false;
    }
}

View &ViewManager::getView(const string &viewName){
    if (views.count(viewName) != 0){
        return views.at(viewName);
    }
    else{
        cerr << "View " << viewName << " does not exist! Returning current view...";
        return *currentView;
    }
}

void ViewManager::drawAll(){
    //1. Check the current view pointer.
    if (currentView){
        //2. Draw every element in every map.
        for (auto& i : currentView->getButtons()){
            if (i.first != "NULL"){
                window->draw(i.second->getSprite());
            }
        }

        for (const auto& i : currentView->getProgressBars()){
            if (i.first != "NULL") {
                for (auto j: i.second->getShapes()) {
                    window->draw(*j);
                }
            }
        }

        for (const auto& i: currentView->getTexts()){
            if (i.first != "NULL") {
                window->draw(*i.second);
            }
        }

        for (const auto& i: currentView->getImages()){
            if (i.first != "NULL") {
                sf::Sprite image(*i.second);
                image.setScale(.15, .15);
                image.setPosition(750, 0);
                window->draw(image);
            }
        }
    }

    else{
        cerr << "Current View is null!";
    }
}

void ViewManager::activateElement(const Vector2i &mouseLocation){
    //1. Check the view pointer.
    if (currentView){
        //2. Call the function if the mouse is over an interactable object (BUTTONS HAVE PRIORITY).
        for (auto& i : currentView->getButtons()){
            if (i.first != "NULL" && i.second->getSprite().getGlobalBounds().contains(Vector2f(mouseLocation))){
                i.second->callFunction();
                break;
            }
        }
    }

    else{
        cerr << "Current View is null!";
    }
}