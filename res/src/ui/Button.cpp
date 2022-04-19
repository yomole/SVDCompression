#include "Button.h"

Button::Button(const string &name, const Texture &baseTexture, const Vector2f &location,
               const std::function<void()> &function) :
SpriteBased(name, baseTexture, location, function){}