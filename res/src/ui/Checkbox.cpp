#include "Checkbox.h"

Checkbox::Checkbox(const string &name, const Texture &baseTexture, const Vector2f &location,
                   const std::function<void(vector<string> &)> &function, vector<string> &arguments, bool checked) :
                   Button(name, baseTexture, location, function, arguments){
    this->checked = checked;
}

bool Checkbox::isChecked() const{
    return checked;
}