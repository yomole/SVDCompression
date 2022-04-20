#include "UIElement.h"

UIElement::UIElement(const string &name, const std::function<void()> &function) {
    this->name = name;
    this->function = function;
}

const string& UIElement::getName() const{
    return name;
}

void UIElement::callFunction(){
    function();
}