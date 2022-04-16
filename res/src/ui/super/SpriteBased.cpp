#include "SpriteBased.h"

SpriteBased::SpriteBased(const string& name, const Texture& baseTexture, const Vector2f& location,
                         const std::function<void(vector<string>&)>& function, vector<string>& arguments)
                         : UIElement(name, arguments, function){
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