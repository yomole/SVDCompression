#pragma once

#include "Button.h"

///@deprecated
/// Basic checkbox class for application.
/// @sa Button
class Checkbox : public Button {

    bool checked;

public:
    /// @brief Constructs a button with a texture, location, and function.
    /// @param name Name of the checkbox.
    /// @param baseTexture Base texture of the checkbox.
    /// @param location Where the checkbox is located in the scene.
    /// @param function Function called when the checkbox is clicked.
    /// @param checked Whether the checkbox is initially checked or not.
    Checkbox(const string& name, const Texture& baseTexture, const Vector2f& location,
             const std::function<void()>& function, bool checked = false);

    /// @returns whether the checkbox has been checked.
    bool isChecked() const;
};
