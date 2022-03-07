#include "SpriteBased.h"

SpriteBased::SpriteBased(const string& name, const Texture& baseTexture, const Vector2f& location,
                         const std::function<void()>& function) : UIElement(name, function){
    this->baseTexture = baseTexture;
    sprite = Sprite(baseTexture);
    sprite.setPosition(location);
}

const Texture& SpriteBased::getBaseTexture() const{
    return baseTexture;
}

Sprite& SpriteBased::getSprite(){
    return this->sprite;
}

void SpriteBased::setTexture(const Texture& texture){
    sprite.setTexture(texture, true);
}