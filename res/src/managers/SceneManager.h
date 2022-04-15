#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "../ui/view/Scene.h"

//USING STATEMENTS:
using std::invalid_argument;
using std::unordered_map;
using sf::RenderWindow;
using sf::Mouse;
using sf::Vector2i;
using sf::Vector2f;

//Forward Declare Scenes.
class Scene;

///Handles each UI element in the application.
class SceneManager {
    static RenderWindow* window; ///< The pointer to the renderwindow object used for the application.
    static unordered_map<string, Scene> scenes;
    static Scene* currentView;
public:

    explicit SceneManager(RenderWindow* window);

    static bool addView(const string& viewName, const string& viewFile);

    static bool changeView(const string& viewName);

    static Scene& getView(const string& viewName);

    static void drawAll();

    static void activateElement(const Vector2i& mouseLocation);

};

