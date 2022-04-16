#include "Button.h"

Button::Button(const string& name, const Texture& baseTexture, const Vector2f& location,
               const std::function<void(vector<string>&)>& function, vector<string>& arguments) :
SpriteBased(name, baseTexture, location, function, arguments){}