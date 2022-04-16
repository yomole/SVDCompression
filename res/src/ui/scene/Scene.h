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
#include "../Checkbox.h"
#include "../functions/ButtonFunctions.h"
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



class Scene {
        string name;

        unordered_map<string, unique_ptr<Button>> buttons;
        unordered_map<string, unique_ptr<Checkbox>> checkboxes;
        unordered_map<string, unique_ptr<ProgressBar>> progressBars;
        unordered_map<string, unique_ptr<Text>> texts;
        unordered_map<string, unique_ptr<Sprite>> images;
public:

    explicit Scene(const string &fileLocation);

    //Creates all UI Elements from a file
    void deserialize(const string &fileLocation);

    void addButton(istringstream &parse);

    void addProgressBar(istringstream &parse);

    void addText(istringstream &parse);

    void addImage(istringstream &parse);

    void addCheckbox(istringstream &parse);

    unordered_map<string, unique_ptr<Button>> &getButtons();

    unordered_map<string, unique_ptr<ProgressBar>> &getProgressBars();

    unordered_map<string, unique_ptr<Text>> &getTexts();

    unordered_map<string, unique_ptr<Sprite>> &getImages();

    unordered_map<string, unique_ptr<Checkbox>> &getCheckboxes();

    unique_ptr<Button> &getButtons(const string &elementName);

    unique_ptr<ProgressBar> &getProgressBars(const string &elementName);

    unique_ptr<Text> &getTexts(const string &elementName);

    unique_ptr<Sprite> &getImages(const string &elementName);

    unique_ptr<Checkbox> &getCheckboxes(const string &elementName);
};