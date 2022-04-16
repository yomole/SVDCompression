#pragma once

#include "Button.h"

class Checkbox : public Button {

    bool checked;

public:
    Checkbox(const string& name, const Texture& baseTexture, const Vector2f& location,
             const std::function<void(vector<string>&)>& function, vector<string>& arguments, bool checked = false);

    bool isChecked() const;
};
