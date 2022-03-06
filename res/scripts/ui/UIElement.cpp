#include "UIElement.h"

UIElement::UIElement(const string& name, const Texture& baseTexture, const Vector2f& location, const std::function<void()>& function){
    this->name = name;
    this->baseTexture = baseTexture;
    this->function = function;

    sprite = Sprite(baseTexture);
    sprite.setPosition(location);
}

const Texture& UIElement::getBaseTexture() const{
    return baseTexture;
}

const string& UIElement::getName() const{
    return name;
}

Sprite& UIElement::getSprite(){
    return this->sprite;
}

void UIElement::setTexture(const Texture& texture){
    sprite.setTexture(texture, true);
}

void UIElement::callFunction() const{
    function();
}