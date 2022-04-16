#include "AssetManager.h"

//Defining static class member variables.
unordered_map<string,Texture> AssetManager::textures;
unordered_map<string,Font> AssetManager::fonts;
set<string> AssetManager::files;
string AssetManager::textureFolder;
string AssetManager::fontFolder;

AssetManager::AssetManager(const string& prefix){
    //1. Set the texture and fonts folder.
    textureFolder = prefix + "res/textures/";
    fontFolder = prefix + "res/fonts/";

    //2. Attempt to load the missing texture.
    if (!addTexture(MISSING_TEXTURE.data())){
        throw std::invalid_argument("[Asset Manager] FATAL! Missing texture was not found! Stopping program...");
    }

    if (!addFont(DEFAULT_FONT.data())){
        throw std::invalid_argument("[Asset Manager] FATAL! Default font was not found! Stopping program...");
    }

    //3. Make the missing texture a repeating texture.
    AssetManager::textures.at(MISSING_TEXTURE.data()).setRepeated(true);
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

bool AssetManager::addImage(const string &fileLocation){
    //1. Create a directory entry from the file location.
    fs::directory_entry iter(fileLocation.data());

    //2. Pull the texture name from the file name.
    string textureName = iter.path().filename().string();

    //2. Check if the file exists.
    if (!iter.exists()){
        cerr << "The image " << fileLocation << " does not exist!" << endl;
        return false;
    }

    //3. Check if it is a valid file type.
    if (!validFile(fileLocation)){
        cerr << "The image " << fileLocation << "is not a valid image type!" << endl;
        return false;
    }

    //1. Look through the textures to see if the name of the texture already exists.
    if (textures.find(textureName) != textures.end()){
        return false;
    }

    //2. Create a new texture and load it from the specified file.
    Texture newText;
    if (!newText.loadFromFile(iter.path().string())){
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
        return(textures.at(MISSING_TEXTURE.data()));
    }

    catch (std::out_of_range& out_of_range2){
        throw std::invalid_argument("[Asset Manager] FATAL! Missing texture was not found! Stopping program...");
    }

}

bool AssetManager::textureExists(const string &textureName){
    return textures.count(textureName) == 1;
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
        return(fonts.at(DEFAULT_FONT.data()));
    }

    catch (std::out_of_range& out_of_range2){
        throw std::invalid_argument("[Asset Manager] FATAL! Default font was not found! Stopping program...");
    }
}

bool AssetManager::addFile(const string &fileLocation){
    //1. Check if the file exists.
    if (!fs::exists(fileLocation)){
        cerr << "File at " << fileLocation << " does not exist!" << endl;
        return false;
    }

    if (validFile(fileLocation)){
        //2. Add the file location to the set.
        files.insert(fileLocation);
    }

    else{
        cerr << "File " << fileLocation << " is not a valid image file!" << endl;
        return false;
    }

    return true;
}

bool AssetManager::addFolder(const string &folderLocation){
    //1. Check if the folder exists.
    if (!fs::exists(folderLocation)){
        cerr << "The folder " << folderLocation << " does not exist!" << endl;
        return false;
    }

    //2. Make an iterator for the directory.
    auto iter = fs::directory_iterator(folderLocation);

    //3. For every file, ensure it is of a valid file type, and then add it to the set of file locations.
    unsigned int numAdded = 0;
    for (const auto& file : iter){
        //Convert file path to string, verify, then add.
        string filePath = file.path().string();
        if (validFile(filePath)){
            files.insert(filePath);
            numAdded++;
        }
    }

    cout << "Added " << numAdded << " files." << endl;

    return true;
}

bool AssetManager::delFile(const string& fileLocation){
    //1. Check if the file exists in the file set.
    if (files.count(fileLocation) == 0){
        cerr << "File " << fileLocation << " was not in the file list!" << endl;
        return false;
    }

    //2. Remove the file from the file set.
    files.erase(fileLocation);

    return true;
}

bool AssetManager::delFolder(const string& folderLocation){
    //1. Check if the folder exists.
    if (!fs::exists(folderLocation)){
        cerr << "The folder " << folderLocation << " does not exist!" << endl;
        return false;
    }

    //2. Make an iterator for the directory.
    auto iter = fs::directory_iterator(folderLocation);

    //3. For every file, try to erase it from the set if possible.
    unsigned int numRemoved = 0;
    for (const auto& file : iter){
        if(files.erase(file.path().string()) == 1){
            numRemoved++;
        }
    }

    cout << "Removed " << numRemoved << " files." << endl;

    return true;
}

bool AssetManager::validFile(const string& filePath){
    //1. Take the filepath and isolate the extension.
    int dot = filePath.find_last_of('.');

    if (dot == string::npos){
        return false;
    }

    string extension = filePath.substr(dot, filePath.length() - dot);

    //2. Check the extension against those supported by the program and SFML.
    for (const string& i : FILE_EXTENSIONS){
        if (extension == i){
            return true;
        }
    }

    return false;
}

set<string>& AssetManager::getFiles(){
    return files;
}

void AssetManager::listFiles(){
    //1. List the files in the file set.

    cout << "Found " << files.size() << " files in the file list:" << endl;
    for (const string& file : files){
        cout << "- " << file << endl;
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
