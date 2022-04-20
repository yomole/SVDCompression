#include "Checkbox.h"

Checkbox::Checkbox(const string &name, const Texture &baseTexture, const Vector2f &location,
                   const std::function<void()> &function, bool checked) :
        Button(name, baseTexture, location, function) {
    this->checked = checked;
}

bool Checkbox::isChecked() const{
    return checked;
}