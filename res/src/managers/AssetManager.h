#pragma once

//INCLUDE STATEMENTS:
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <filesystem>
#include <SFML/Graphics.hpp>

//USING STATEMENTS:
using std::string;
using std::unordered_map;
using std::set;
using std::pair;
using std::out_of_range;
using std::istringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::exception;
using std::getline;
using std::cerr;
using std::string_view;

namespace fs = std::filesystem;

using sf::Texture;
using sf::Font;
using sf::Image;

//CONSTANTS:
static const string_view MISSING_TEXTURE = "_missingtexture.png";
static const string_view DEFAULT_FONT = "OpenSans-Regular400.ttf";

static const unsigned int NUM_EXTENSIONS = 4;
static const string_view FILE_EXTENSIONS[NUM_EXTENSIONS] = {".jpg", ".png", ".bmp", ".tga"};

//ENUMS:
enum FILESET{
    NORMAL,
    COMPRESSED
};

///Handles asset loading and assignment for the entire application.
///Assets include textures, fonts, and files.
class AssetManager {
    static string prefix; ///< Prefix used to access files outside of bin/

    static unordered_map<string,Texture> textures; ///< Texture map for easy access using the name of the texture.
    static string textureFolder; ///< Location of the texture folder.

    static unordered_map<string, Font> fonts; ///< Font map for easy access using the name of the font.
    static string fontFolder; ///< Location of the font folder.

    static set<string> files; ///< Set of file locations for image processing.
    static set<string> compressedFiles; ///< Set containing the file names compressed by the program that are in textures.
    static string outputFolder; ///< Location of the output folder for the compressed images.

public:
    /// Default Constructor.
    /// Generates the AssetManager class with the default texture location prefix + "res/textures".
    /// Also creates a missing texture for later use.
    /// @param prefix the path from the executable to the folder containing res/. The default is a blank string.
    /// @warning requires that the missing texture and default font exist within res/textures and res/fonts.
    explicit AssetManager(const string &prefixIn = prefix);

    /* * * * * * * * * * *
     * TEXTURE FUNCTIONS *
     * * * * * * * * * * */

    /// @brief Adds the texture with the specified name to the asset manager.
    /// @param textureName the filename of the texture to be added.
    /// @returns true if the texture was successfully added.
    static bool addTexture(const string& textureName);

    /// @brief Adds the image with the specified name to the asset manager.
    /// @param fileLocation the location of the texture to be added.
    /// @returns true if the image was successfully added.
    static bool addImage(const string& fileLocation);

    /// @brief Adds the passed-in image to the asset manager.
    /// @param image the image to be added.
    /// @param fileLocation the location of the image to be added.
    /// @note Since the image is added from a created image, the file location does not have to exist.
    /// @returns true if the image was successfully added.
    static bool addImage(const Image& image, const string &fileLocation);

    /// @brief Adds the image with the specified name to the asset manager.
    /// @param image the image to be added.
    /// @param fileLocation the location where the image should be saved, including filename and extension.
    /// @returns true if the image was successfully added.
    static bool exportImage(const Image& image, const string& fileLocation);

    /// @brief Accessor for the texture map.
    /// @param textureName the filename of the target texture.
    /// @returns a reference to the texture in the map if it exists. Otherwise, it returns the missing texture.
    static const Texture& getTexture(const string& textureName);

    static bool textureExists(const string& textureName);

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

    static bool addFile(const string& fileLocation, int fileset = NORMAL);

    static bool addFolder(const string& folderLocation, int fileset = NORMAL);

    static bool delFile(const string& fileLocation, int fileset = NORMAL);

    static bool delFolder(const string& folderLocation, int fileset = NORMAL);

    static bool validFile(const string& filePath);

    static set<string>& getFiles();

    static set<string>& getCompressedFiles();

    static void listFiles(int fileset = NORMAL);

    /* * * * * * * * * * * *
     * SERIALIZE FUNCTIONS *
     * * * * * * * * * * * */

    /// @brief Loads all assets into the asset manager from their respective folders.
    static void loadAll();

    /// @brief Converts the space-separated file produced by the SVD algorithm to an image file readable by SFML.
    static bool csvToImage(const string& fileLocation, const string& fileFormat = "png");

    /* * * * * * * * * * * * * *
     * MISCELLANEOUS FUNCTIONS *
     * * * * * * * * * * * * * */

    ///@brief Returns the prefix loaded into the AssetManager.
    static const string& getPrefix();

    ///@brief Sets the prefix for the AssetManager.
    ///@sa AssetManager();
    static void setPrefix(const string& prefixIn);
};
