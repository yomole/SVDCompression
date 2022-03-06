#include "TextureManager.h"

//Defining static class member variables.
map<string,Texture> TextureManager::textures;
string TextureManager::textureFolder;

TextureManager::TextureManager(const string& prefix){
    //1. Set the texture folder.
    textureFolder = prefix + "res/textures/";

    //2. Attempt to load the missing texture.
    if (!addTexture(MISSING_TEXTURE)){
        throw std::invalid_argument("[Texture Manager] FATAL! Missing texture was not found! Stopping program...");
    }

    //3. Make the missing texture a repeating texture.
    TextureManager::textures.at(MISSING_TEXTURE).setRepeated(true);
}

bool TextureManager::addTexture(const string& textureName) {
    //1. Look through the textures to see if the name of the texture already exists.
    if (textures.find(textureName) != textures.end()){
        return false;
    }

    //2. Create a new texture and load it from the specified file.
    Texture newText;
    if (!newText.loadFromFile(textureFolder + textureName)){
        return false;
    }

    //3. Put it into the map.
    textures.insert(pair<string, Texture>(textureName, newText));

    return true;
}

const Texture& TextureManager::getTexture(const string& textureName){
    //1. Try to access the texture with the given file name.
    try{
        return(textures.at(textureName));
    }

    catch (std::out_of_range& out_of_range){
        cout << "[Texture Manager] Texture named " + textureName + " was not found! Loading missing texture..." << endl;
    }

    //2. If the texture was not found, return the missing texture.
    try{
        return(textures.at(MISSING_TEXTURE));
    }

    catch (std::out_of_range& out_of_range2){
        throw std::invalid_argument("[Texture Manager] FATAL! Missing texture was not found! Stopping program...");
    }

}