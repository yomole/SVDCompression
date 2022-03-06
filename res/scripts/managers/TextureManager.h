#pragma once

//INCLUDE STATEMENTS:
#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

//USING STATEMENTS:
using std::string;
using std::map;
using std::pair;
using std::out_of_range;
using std::cout;
using std::endl;
using std::cerr;

using sf::Texture;

//CONSTANTS:
const string MISSING_TEXTURE = "_missingtexture.png";

/// @class Static class that Handles texture loading and assignment for the entire application.
class TextureManager {

    /// Stores the textures in a map for easy access using the name of the texture.
    static map<string,Texture> textures;

    ///Location of the texture folder.
    static string textureFolder;

public:
    /// Default Constructor.
    /// Generates the TextureManager class with the default textureLocation prefix + "res/textures".
    /// Also creates a missing texture texture for later use.
    /// @param prefix the path from the executable to the folder containing res/. Default is a blank string.
    explicit TextureManager(const string& prefix = "");

    /// Adds the texture with the specified name to the textureManager.
    /// @param textureName the filename of the texture to be added.
    /// @returns true if the texture was successfully added.
    static bool addTexture(const string& textureName);

    /// Accessor for the texture map.
    /// @param textureName the filename of the target texture.
    /// @returns a reference to the texture in the map if it exists. Otherwise, it returns a texture representing a
    /// missing texture, and prints an error to the log.
    const static Texture& getTexture(const string& textureName);
};
