#include "SceneManager.h"

//Static class variable initialization.
RenderWindow* SceneManager::window;
unordered_map<string, Scene> SceneManager::scenes;
Scene* SceneManager::currentView;

SceneManager::SceneManager(RenderWindow* window){
    //If the UI Element Manager is created without a valid renderwindow pointer, throw an exception.
    if (window == nullptr){
        throw invalid_argument("SceneManager initialized without a valid renderwindow pointer!");
    }

    SceneManager::window = window;
    SceneManager::currentView = nullptr;
}

bool SceneManager::addView(const string &viewName, const string &viewFile){
    if (scenes.count(viewName) == 0) {
        scenes.insert(pair<string, Scene>(viewName, Scene(viewFile)));
        return true;
    }
    else{
        return false;
    }
}

bool SceneManager::changeView(const string &viewName){
    if (scenes.count(viewName) != 0){
        currentView = &(scenes.at(viewName));
        return true;
    }
    else{
        return false;
    }
}

Scene& SceneManager::getView(const string &viewName){
    if (scenes.count(viewName) != 0){
        return scenes.at(viewName);
    }
    else{
        cerr << "Scene " << viewName << " does not exist! Returning current scene...";
        return *currentView;
    }
}

void SceneManager::drawAll(){
    //1. Check the current scene pointer.
    if (currentView){
        //2. Draw every element in every map.
        for (auto& i : currentView->getButtons()){
            if (i.first != "NULL"){
                window->draw(i.second->getSprite());
            }
        }

        for (auto& i : currentView->getProgressBars()){
            if (i.first != "NULL") {
                for (auto j: i.second->getShapes()) {
                    window->draw(*j);
                }
            }
        }

        for (auto& i: currentView->getTexts()){
            if (i.first != "NULL") {
                window->draw(*i.second);
            }
        }

        for (auto& i: currentView->getImages()){
            if (i.first != "NULL") {
                window->draw(*i.second);
            }
        }

        for (auto& i: currentView->getCheckboxes()){
            if (i.first != "NULL"){
                window->draw(i.second->getSprite());
            }
        }
    }

    else{
        cerr << "Current Scene is null!";
    }
}

void SceneManager::activateElement(const Vector2i &mouseLocation){
    //1. Check the scene pointer.
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
        cerr << "Current Scene is null!";
    }
}