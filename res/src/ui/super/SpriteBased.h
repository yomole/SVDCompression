#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include "UIElement.h"

//USING STATEMENTS:
using sf::Texture;
using sf::Sprite;

///Subclass dealing with sprite-based UI elements.
class SpriteBased : public UIElement{

protected:

    Texture baseTexture; ///<Initial texture for the UI Element.
    Sprite sprite; ///<Sprite of the UI Element.

public:

    /// @brief Default Constructor. Creates the Sprite-based UI element.
    /// @param name name of the UI element.
    /// @param baseTexture the default texture of the UI element.
    /// @param location the default location of the UI element.
    /// @param function the embedded function of the  UI element.
    SpriteBased(const string& name, const Texture& baseTexture, const Vector2f& location,
                const std::function<void(vector<string>&)>& function, vector<string>& arguments);

    /// @brief base texture accessor.
    /// @returns the base texture of the UI element.
    const Texture& getBaseTexture() const;

    /// @brief sprite accessor.
    /// @returns the sprite of the UI element.
    Sprite& getSprite();
};
