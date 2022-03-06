#pragma once

//INCLUDE STATEMENTS:
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../ui/UIElement.h"

//USING STATEMENTS:
using std::forward_list;
using std::invalid_argument;

using sf::RenderWindow;
using sf::Mouse;
using sf::Vector2i;
using sf::Vector2f;

/// @class Static class that handles each UI element in the application.
class UIElementManager {
    static RenderWindow* window; ///< The pointer to the renderwindow object used for the application.
    static forward_list<UIElement*> elements; ///< Stores the elements in a map for easy access using the name of the element.
public:

    UIElementManager(RenderWindow* window);

    static bool addElement(UIElement* element);
    static void drawAllElements();

    /// Tries to find an element within the mouse coordinates and activates its function.
    /// @param mouseLocation Location of the mouse
    static void activateElement(const Vector2i& mouseLocation);

};

