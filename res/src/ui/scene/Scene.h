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

/// A grouping of UI elements that are drawn together by the scene manager.
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

    ///@returns All button objects in the scene in the form of a map reference.
    unordered_map<string, unique_ptr<Button>> &getButtons();

    ///@deprecated
    ///@returns All progress bar objects in the scene in the form of a map reference.
    unordered_map<string, unique_ptr<ProgressBar>> &getProgressBars();

    ///@returns All text objects in the scene in the form of a map reference.
    unordered_map<string, unique_ptr<Text>> &getTexts();

    ///@returns All image objects in the scene in the form of a map reference.
    unordered_map<string, unique_ptr<Sprite>> &getImages();

    ///@deprecated
    ///@returns All checkbox objects in the scene in the form of a map reference.
    unordered_map<string, unique_ptr<Checkbox>> &getCheckboxes();

    /* * * * * * * * * * *
     * ELEMENT ACCESSORS *
     * * * * * * * * * * */

    unique_ptr<Button> &getButtons(const string &elementName);

    ///@deprecated
    ///@returns A progress bar in the scene with a given name.
    ///@warning If the progress bar does not exist, a null pointer is returned!
    unique_ptr<ProgressBar> &getProgressBars(const string &elementName);

    ///@returns A text object in the scene with a given name.
    ///@warning If the progress bar does not exist, a null pointer is returned!
    unique_ptr<Text> &getTexts(const string &elementName);

    ///@returns An image object in the scene with a given name.
    ///@warning If the progress bar does not exist, a null pointer is returned!
    unique_ptr<Sprite> &getImages(const string &elementName);

    ///@deprecated
    ///@returns A checkbox object in the scene with a given name.
    ///@warning If the progress bar does not exist, a null pointer is returned!
    unique_ptr<Checkbox> &getCheckboxes(const string &elementName);

    /* * * * * * * * * * * * * * * * *
     * SERIALIZE & PARSING FUNCTIONS *
     * * * * * * * * * * * * * * * * */

    ///@deprecated
    ///Parses the arguments of a UI element from a scene file.
    void parseArgs(istringstream& parse, vector<string>& args);
};