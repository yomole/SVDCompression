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
        unordered_map<string, unique_ptr<Button>> buttons;
        unordered_map<string, unique_ptr<Checkbox>> checkboxes;
        unordered_map<string, unique_ptr<ProgressBar>> progressBars;
        unordered_map<string, unique_ptr<Text>> texts;
        unordered_map<string, unique_ptr<Sprite>> images;
public:

    ///@brief Creates a blank scene.
    Scene();

    /* * * * * * * * * * * * *
     * ELEMENT  CONSTRUCTORS *
     * * * * * * * * * * * * */

    void addButton(const string& elementName, const string& textureName, const Vector2f& position,
                   const function<void()>& function);

    void addText(const string& elementName, const Vector2f& position, const Font& font, unsigned int fontSize,
                 const string& text);

    void addImage(const string& elementName, const string& fileLocation, const Vector2f& position,
                 const Vector2f& scale = Vector2f(1, 1));

    /* * * * * * * * *
     * MAP ACCESSORS *
     * * * * * * * * */

    unordered_map<string, unique_ptr<Button>> &getButtons();

    ///@deprecated
    unordered_map<string, unique_ptr<ProgressBar>> &getProgressBars();

    unordered_map<string, unique_ptr<Text>> &getTexts();

    unordered_map<string, unique_ptr<Sprite>> &getImages();

    ///@deprecated
    unordered_map<string, unique_ptr<Checkbox>> &getCheckboxes();

    /* * * * * * * * * * *
     * ELEMENT ACCESSORS *
     * * * * * * * * * * */

    unique_ptr<Button> &getButtons(const string &elementName);

    ///@deprecated
    unique_ptr<ProgressBar> &getProgressBars(const string &elementName);

    unique_ptr<Text> &getTexts(const string &elementName);

    unique_ptr<Sprite> &getImages(const string &elementName);

    ///@deprecated
    unique_ptr<Checkbox> &getCheckboxes(const string &elementName);

    /* * * * * * * * * * * * * * * * *
     * SERIALIZE & PARSING FUNCTIONS *
     * * * * * * * * * * * * * * * * */

    //Parses the arguments of a UI element.
    ///@deprecated
    void parseArgs(istringstream& parse, vector<string>& args);
};