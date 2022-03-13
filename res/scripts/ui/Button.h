#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "super/UIElement.h"
#include "super/SpriteBased.h"

//USING STATEMENTS:
using std::function;
using std::string;

using sf::Texture;
using sf::Vector2f;

/// @brief Button class for the UI using SFML.
/// @details button class is a customizable, basic class for a 1 function button.
class Button : public SpriteBased{
public:
    Button(const string& name, const Texture& baseTexture, const Vector2f& location, const std::function<void()>& function);
};