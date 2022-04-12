#include "ProgressBar.h"

ProgressBar::ProgressBar(const string &name, const Vector2f& size, const Vector2f& position) : UIElement(name){
    //1. Create the outline for the progress bar.
    outline = RectangleShape(size);
    outline.setFillColor(Color::Transparent);
    outline.setOutlineColor(Color::Black);
    outline.setOutlineThickness(1);
    outline.setPosition(position);

    //2. Create the bar for the progress bar.
    bar = RectangleShape(Vector2f(0, size.y));
    bar.setFillColor(Color::Green);
    bar.setOutlineColor(Color::Transparent);
    bar.setPosition(position);

    //3. Put both shapes in the list.
    shapes.push_front(&outline);
    shapes.push_front(&bar);
}

void ProgressBar::setPercentage(float percentage) {
    this->percentage = percentage;

    if (percentage < 1) {
        bar.setSize(Vector2f(percentage * (outline.getSize().x - outline.getOutlineThickness()), bar.getSize().y));
    }
    else{
        bar.setSize(Vector2f(outline.getSize().x, bar.getSize().y));
    }
}

const float& ProgressBar::getPercentage() const {
    return this->percentage;
}

const forward_list<RectangleShape*>& ProgressBar::getShapes() const {
    return this->shapes;
}
