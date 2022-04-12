#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Button.h"
#include "../ProgressBar.h"
#include "../../managers/AssetManager.h"

using std::unordered_map;
using std::string;
using std::ifstream;
using std::istringstream;
using std::getline;
using std::exception;
using std::cerr;
using std::stof;
using std::stoi;
using std::pair;
using std::unique_ptr;
using std::function;
using sf::Text;
using sf::Image;
using sf::Font;
using sf::Texture;
using sf::Color;
using sf::Vector2f;

class View {
    string name;

    unordered_map<string, unique_ptr<Button>> buttons;
    unordered_map<string, unique_ptr<ProgressBar>> progressBars;
    unordered_map<string, unique_ptr<Text>> texts;
    unordered_map<string, unique_ptr<Texture>> images;
public:

    View(const string& fileLocation);

    //Creates all UI Elements from a file.
    void serialize(const string& fileLocation);

    void addButton(const string& elementName, Vector2f position, const string& textureName, const function<void()>& function);
    void addProgressBar(istringstream& parse);
    void addText(istringstream& parse);
    void addImage(istringstream& parse);

    unordered_map<string, unique_ptr<Button>>& getButtons();
    unordered_map<string, unique_ptr<ProgressBar>>& getProgressBars();
    unordered_map<string, unique_ptr<Text>>& getTexts();
    unordered_map<string, unique_ptr<Texture>>& getImages();

    unique_ptr<Button>& getButton(const string& elementName);
    unique_ptr<ProgressBar>& getProgressBar(const string& elementName);
    unique_ptr<Text>& getText(const string& elementName);
    unique_ptr<Texture>& getImage(const string& elementName);

};