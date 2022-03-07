#pragma once

//INCLUDE STATEMENTS:
#include <SFML/Graphics.hpp>
#include <string>

#include "UIElement.h"

//USING STATEMENTS:
using std::string;

using sf::Text;
using sf::Color;
using sf::Vector2f;

class TextBased : public UIElement {
public:
    Text text;

    ///@brief constructor using a string.
    ///@param name: name of the text-based UI element.
    ///@param position: location of the text on the screen.
    ///@param font: font of the text.
    ///@param text: string to change the text to.
    ///@param color: color to change the text to.
    TextBased(const string& name, const Vector2f& position, const sf::Font& font, const string& text = "Bottom Text",
              const Color& color = Color::Black);

    ///@brief constructor using a sf::Text class object.
    ///@param name: name of the text-based UI element.
    ///@param position: location of the text on the screen.
    ///@param font: font of the text.
    ///@param text: the sf::Text class object to replace the current text.
    ///@param color: color to change the text to.
    TextBased(const string& name, const Vector2f& position, const sf::Font& font, const Text& text,
              const Color& color = Color::Black);

};
