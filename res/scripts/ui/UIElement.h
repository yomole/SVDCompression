#pragma once

//INCLUDE STATEMENTS:
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>

//USING STATEMENTS:
using std::string;
using std::function;

using sf::Texture;
using sf::Sprite;
using sf::Vector2f;

///A Base class for all UI elements.
class UIElement {

protected:
    string name; ///<Name of the UI Element.
    Texture baseTexture; ///<Initial texture for the UI Element.
    Sprite sprite; ///<Sprite of the UI Element.
    function<void()> function; ///< Function embedded in the UI element.

public:
    /// Default Constructor. Creates the UI element with the specified name and initial texture.
    UIElement(const string& name, const Texture& baseTexture, const Vector2f& location, const std::function<void()>& function);

    ///@brief base texture accessor.
    ///@returns the base texture of the UI element.
    const Texture& getBaseTexture() const;

    ///@brief name accessor.
    ///@returns the name of the UI element.
    const string& getName() const;

    ///@brief sprite accessor.
    ///@returns the sprite of the UI element.
    Sprite& getSprite();

    void setTexture(const Texture& texture);

    ///@brief calls the function embedded in the UI element.
    void callFunction() const;
};
