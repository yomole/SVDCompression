#pragma once

//INCLUDE STATEMENTS:
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <filesystem>
#include <SFML/Graphics.hpp>

//USING STATEMENTS:
using std::string;
using std::unordered_map;
using std::set;
using std::pair;
using std::out_of_range;
using std::cout;
using std::endl;
using std::cerr;
using std::string_view;

namespace fs = std::filesystem;

using sf::Texture;
using sf::Font;

//CONSTANTS:
static const string_view MISSING_TEXTURE = "_missingtexture.png";
static const string_view DEFAULT_FONT = "OpenSans-Regular400.ttf";

///Handles asset loading and assignment for the entire application.
class AssetManager {

    static unordered_map<string,Texture> textures; ///< Texture map for easy access using the name of the texture.
    static string textureFolder; ///< Location of the texture folder.

    static unordered_map<string, Font> fonts; ///< Font map for easy access using the name of the font.
    static string fontFolder; ///< Location of the font folder.

    static set<string> files; ///< Set of file locations for image processing.

public:
    /// Default Constructor.
    /// Generates the AssetManager class with the default texture location prefix + "res/textures".
    /// Also creates a missing texture for later use.
    /// @param prefix the path from the executable to the folder containing res/. The default is a blank string.
    /// @warning requires that the missing texture and default font exist within res/textures and res/fonts.
    explicit AssetManager(const string& prefix = "");

    /* * * * * * * * * * *
     * TEXTURE FUNCTIONS *
     * * * * * * * * * * */

    /// @brief Adds the texture with the specified name to the asset manager.
    /// @param textureName the filename of the texture to be added.
    /// @returns true if the texture was successfully added.
    static bool addTexture(const string& textureName);

    /// @brief Accessor for the texture map.
    /// @param textureName the filename of the target texture.
    /// @returns a reference to the texture in the map if it exists. Otherwise, it returns the missing texture.
    static const Texture& getTexture(const string& textureName);

    /* * * * * * * * * *
     * FONT  FUNCTIONS *
     * * * * * * * * * */

    /// @brief Adds the font with the specified name to the asset manager.
    /// @param fontName the filename of the font to be added.
    /// @returns true if the font was successfully added.
    static bool addFont(const string& fontName);

    /// @brief Accessor for the font map.
    /// @param fontName the filename of the target texture.
    /// @returns a reference to the font in the map if it exists. Otherwise, it returns the default font.
    static const Font& getFont(const string& fontName);

    /* * * * * * * * * * *
     * FILE    FUNCTIONS *
     * * * * * * * * * * */

    static bool addFile(const string& fileLocation);

    static bool delFile(const string& fileLocation);

    static void listFiles();

    /* * * * * * * * * * * *
     * SERIALIZE FUNCTIONS *
     * * * * * * * * * * * */

    /// @brief Loads all assets into the asset manager from their respective folders.
    static void loadAll();

};
