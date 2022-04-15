#include "UIElement.h"

UIElement::UIElement(const string& name, vector<string>& arguments,
                     const std::function<void(vector<string>&)>& function){
    this->name = name;
    this->function = function;
    this->arguments = arguments;
}

const string& UIElement::getName() const{
    return name;
}

void UIElement::callFunction(){
    function(arguments);
}