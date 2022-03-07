#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "UIElement.h"
#include "SpriteBased.h"

//USING STATEMENTS:
using std::function;
using std::string;

using sf::Texture;
using sf::Vector2f;

///Button class for the UI using SFML
///The button class is a customizable, basic class for a 1 function button.
class Button : public SpriteBased{
public:
    Button(const string& name, const Texture& baseTexture, const Vector2f& location, const std::function<void()>& function);
};