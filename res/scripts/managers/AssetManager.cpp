#include "AssetManager.h"

//Defining static class member variables.
map<string,Texture> AssetManager::textures;
map<string,Font> AssetManager::fonts;
string AssetManager::textureFolder;
string AssetManager::fontFolder;

AssetManager::AssetManager(const string& prefix){
    //1. Set the texture and fonts folder.
    textureFolder = prefix + "res/textures/";
    fontFolder = prefix + "res/fonts/";

    //2. Attempt to load the missing texture.
    if (!addTexture(MISSING_TEXTURE)){
        throw std::invalid_argument("[Asset Manager] FATAL! Missing texture was not found! Stopping program...");
    }

    if (!addFont(DEFAULT_FONT)){
        throw std::invalid_argument("[Asset Manager] FATAL! Default font was not found! Stopping program...");
    }

    //3. Make the missing texture a repeating texture.
    AssetManager::textures.at(MISSING_TEXTURE).setRepeated(true);
}

bool AssetManager::addTexture(const string& textureName) {
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

const Texture& AssetManager::getTexture(const string& textureName){
    //1. Try to access the texture with the given file name.
    try{
        return(textures.at(textureName));
    }

    catch (std::out_of_range& out_of_range){
        cout << "[Asset Manager] Texture named " + textureName + " was not found! Loading missing texture..." << endl;
    }

    //2. If the texture was not found, return the missing texture.
    try{
        return(textures.at(MISSING_TEXTURE));
    }

    catch (std::out_of_range& out_of_range2){
        throw std::invalid_argument("[Asset Manager] FATAL! Missing texture was not found! Stopping program...");
    }

}

bool AssetManager::addFont(const string &fontName){
    //1. Look through the fonts to see if the name of the texture already exists.
    if (fonts.find(fontName) != fonts.end()){
        return false;
    }

    //2. Create a new texture and load it from the specified file.
    Font newFont;
    if (!newFont.loadFromFile(fontFolder + fontName)){
        return false;
    }

    //3. Put it into the map.
    fonts.insert(pair<string, Font>(fontName, newFont));

    return true;
}

const Font &AssetManager::getFont(const string &fontName){
    //1. Try to access the texture with the given file name.
    try{
        return(fonts.at(fontName));
    }

    catch (std::out_of_range& out_of_range){
        cout << "[Asset Manager] Font named " + fontName + " was not found! Loading default font..." << endl;
    }

    //2. If the texture was not found, return the missing texture.
    try{
        return(fonts.at(DEFAULT_FONT));
    }

    catch (std::out_of_range& out_of_range2){
        throw std::invalid_argument("[Asset Manager] FATAL! Default font was not found! Stopping program...");
    }
}

void AssetManager::loadAll(){
    cout << "Loading textures..." << endl;

    //1. Construct a directory iterator with the file path for textures
    fs::directory_iterator textureIter((fs::path(textureFolder)));

    //2. For each file in the directory, add the texture to the asset manager.
    for (const auto &file : textureIter){
        cout << "\t- " << file.path();
        if (addTexture(file.path().filename().string())){
            cout << " loaded!" << endl;
        }
        else{
            cout << " was already loaded!" << endl;
        }
    }

    cout << "Loading fonts..." << endl;

    //3. Construct a directory iterator with the file path for fonts.
    fs::directory_iterator fontIter((fs::path(fontFolder)));

    //4. For each file in the directory, add the font to the asset manager.
    for (const auto &file : fontIter){
        cout << "\t- " << file.path();
        if (addFont(file.path().filename().string())){
            cout << " loaded!" << endl;
        }
        else{
            cout << " was already loaded!" << endl;
        }
    }
}