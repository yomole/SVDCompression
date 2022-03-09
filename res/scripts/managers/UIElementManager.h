#pragma once

//INCLUDE STATEMENTS:
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../ui/SpriteBased.h"
#include "../ui/TextBased.h"

//USING STATEMENTS:
using std::forward_list;
using std::invalid_argument;

using sf::RenderWindow;
using sf::Mouse;
using sf::Vector2i;
using sf::Vector2f;

///Handles each UI element in the application.
class UIElementManager {
    static RenderWindow* window; ///< The pointer to the renderwindow object used for the application.
    static forward_list<SpriteBased*> elements; ///< Stores the elements in a map for easy access using the name of the element.
    static forward_list<TextBased*> text; ///< Stores text in a map for easy access using the name of the text.
public:

    UIElementManager(RenderWindow* window);

    ///@brief adds an element based on a pointer to the element.
    ///@param element pointer to a sprite-based UI element.
    static bool addElement(SpriteBased* element);

    ///@brief adds text based on a pointer to the text.
    ///@param text pointer to the text-based UI element.
    static bool addElement(TextBased* text);

    ///@brief draws everything that is visible and stored in the UI element manager.
    static void drawAll();

    /// Tries to find an element within the mouse coordinates and activates its function.
    /// @param mouseLocation Location of the mouse
    static void activateElement(const Vector2i& mouseLocation);

};

