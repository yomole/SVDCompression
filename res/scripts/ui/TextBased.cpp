#include "TextBased.h"

TextBased::TextBased(const string& name, const Vector2f& position, const sf::Font& font, const string& text,
                     const Color &color) : UIElement(name){
    this->text.setString(text);
    this->text.setPosition(position);
    this->text.setFillColor(color);
    this->text.setFont(font);
}

TextBased::TextBased(const string& name, const Vector2f& position, const sf::Font& font, const Text& text,
                     const Color &color) : UIElement(name){
    this->text = text;
    this->text.setPosition(position);
    this->text.setFillColor(color);
    this->text.setFont(font);
}