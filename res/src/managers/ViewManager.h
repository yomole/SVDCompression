#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "../ui/view/View.h"

//USING STATEMENTS:
using std::invalid_argument;
using std::unordered_map;

using sf::RenderWindow;
using sf::Mouse;
using sf::Vector2i;
using sf::Vector2f;

///Handles each UI element in the application.
class ViewManager {
    static RenderWindow* window; ///< The pointer to the renderwindow object used for the application.
    static unordered_map<string, View> views;
    static View* currentView;
public:

    explicit ViewManager(RenderWindow* window);

    static bool addView(const string& viewName, const string& viewFile);

    static bool changeView(const string& viewName);

    static View& getView(const string& viewName);

    static void drawAll();

    static void activateElement(const Vector2i& mouseLocation);

};

