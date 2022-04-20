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
    /// @param name Name of the UI element.
    /// @param baseTexture The default texture of the UI element.
    /// @param location The default location of the UI element.
    /// @param function The embedded function of the  UI element.
    SpriteBased(const string& name, const Texture& baseTexture, const Vector2f& location,
                const std::function<void()> &function);

    /// @returns The base texture of the UI element.
    const Texture& getBaseTexture() const;

    /// @returns A reference to the sprite of the UI element.
    Sprite& getSprite();
};
