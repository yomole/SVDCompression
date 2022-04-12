#pragma once

//INCLUDE STATEMENTS:
#include <SFML/graphics.hpp>
#include <string>
#include <forward_list>

#include "super/UIElement.h"

//USING STATEMENTS:
using std::string;

using sf::RectangleShape;
using sf::Vector2f;
using sf::Color;
using std::forward_list;

class ProgressBar : public UIElement {

    RectangleShape bar;
    RectangleShape outline;
    forward_list<RectangleShape*> shapes;

    float percentage;

public:

    explicit ProgressBar(const string& name, const Vector2f& size, const Vector2f& position = Vector2f(0,0));

    void setPercentage(float percentage);
    const float& getPercentage() const;

    const forward_list<RectangleShape*>& getShapes() const;
};
