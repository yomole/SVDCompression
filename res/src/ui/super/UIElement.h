#pragma once

//INCLUDE STATEMENTS:
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

//USING STATEMENTS:
using std::string;
using std::function;
using std::vector;
using sf::Texture;
using sf::Sprite;
using sf::Vector2f;

///A Base class for all UI elements.
class UIElement {

protected:
    string name; ///<Name of the UI Element.
    function<void()> function; ///< Function embedded in the UI element.
public:
    /// Default Constructor. Creates the UI element with the specified name and embedded function.
    /// @param name Name of the UI element.
    /// @param function Function to embed in the UI Element. Default is no operation.
    UIElement(const string &name, const std::function<void()>& function = []() -> void {});

    ///@returns the name of the UI element.
    const string& getName() const;

    ///@brief calls the function embedded in the UI element.
    void callFunction();
};
