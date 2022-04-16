#pragma once

//INCLUDE STATEMENTS:
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

//USING STATEMENTS:
using std::string;
using std::function;
using std::vector;
using sf::Texture;
using sf::Sprite;
using sf::Vector2f;

///A Base class for all UI elements.
class UIElement {

protected:
    string name; ///<Name of the UI Element.
    function<void(vector<string>&)> function; ///< Function embedded in the UI element.
    vector<string> arguments;
public:
    /// Default Constructor. Creates the UI element with the specified name and embedded function.
    UIElement(const string& name, vector<string>& arguments,
                       const std::function<void(vector<string>&)>& function = [](vector<string>&)->void{});

    ///@brief name accessor.
    ///@returns the name of the UI element.
    const string& getName() const;

    ///@brief calls the function embedded in the UI element.
    void callFunction();
};
