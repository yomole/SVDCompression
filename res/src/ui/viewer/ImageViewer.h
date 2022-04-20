#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "../Button.h"
#include "../../managers/AssetManager.h"
#include "../../managers/SceneManager.h"

namespace fs = std::filesystem;
using std::unique_ptr;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::to_string;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Event;
using sf::Vector2u;

//CONSTANTS:
const float VIDEOMODE_SCALE = 2;
const unsigned int IMAGE_MARGIN = 8;

///@brief Image viewer for a single image file.
///@param fileLocation The location of the image to view.
void showImage(const string& fileLocation);

///@brief A side by side image viewer for the original and compressed image files.
void showImages();

///@brief Updates the text containing file name and file sizes.
///@param origFile The original uncompressed file's location.
///@param compFile The compressed file's location.
///@param scene The image viewer scene.
void updateText(const string& origFile, const string& compFile, Scene& scene);

///@brief A function that adjusts the size of the window to the size of the contents contained within.
///@param window A reference to the renderwindow we are adjusting.
///@param scene The image viewer scene.
void adjustWindow(sf::RenderWindow& window, Scene& scene);