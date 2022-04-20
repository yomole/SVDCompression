#include "AssetManager.h"

//Defining static class member variables.
unordered_map<string,Texture> AssetManager::textures;
unordered_map<string,Font> AssetManager::fonts;
set<string> AssetManager::files;
set<string> AssetManager::compressedFiles;
bool AssetManager::loaded = false;
string AssetManager::prefix;
string AssetManager::textureFolder;
string AssetManager::fontFolder;
string AssetManager::outputFolder;

AssetManager::AssetManager(const string& prefixIn){
    //1. Set the texture and fonts folder.
    textureFolder = prefix + "res/textures/";
    fontFolder = prefix + "res/fonts/";
    outputFolder = prefix + "output/";

    //3. Attempt to load the missing texture and default font.
    if (!addTexture(MISSING_TEXTURE.data()) && textures.count(MISSING_TEXTURE.data()) == 0){
        throw std::invalid_argument("[Asset Manager] FATAL! Missing texture was not found! Stopping program...");
    }

    if (!addFont(DEFAULT_FONT.data()) && fonts.count(DEFAULT_FONT.data()) == 0){
        throw std::invalid_argument("[Asset Manager] FATAL! Default font was not found! Stopping program...");
    }

    //4. Make the missing texture a repeating texture.
    AssetManager::textures.at(MISSING_TEXTURE.data()).setRepeated(true);

    loadAll();
    loaded = true;
}

bool AssetManager::addTexture(const string& textureName) {
    //1. Look through the textures to see if the name of the texture already exists.
    if (textures.count(textureName) == 1){
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
    //1. Pull the texture name from the file name.
    string textureName = fs::path(fileLocation).filename().string();

    //2. Check if the file exists.
    if (!fs::exists(fileLocation)){
        cerr << "The image " << fileLocation << " does not exist!" << endl;
        return false;
    }

    //3. Check if it is a valid file type.
    if (!validFile(fileLocation)){
        cerr << "The image " << fileLocation << "is not a valid image type!" << endl;
        return false;
    }

    //2. Create a new texture and load it from the specified file.
    Texture newText;
    if (!newText.loadFromFile(fileLocation)){
        return false;
    }

    //3. Put it into the texture map.
    if(!textures.insert(pair<string, Texture>(textureName, newText)).second){
        cerr << "The image " << fileLocation << " could not be inserted into the Asset Manager textures as "
        << textureName << endl;
        return false;
    }

    return true;
}

bool AssetManager::addImage(const Image& image, const string &fileLocation){
    //1. Check if it is a valid file type.
    if (!validFile(fileLocation)){
        cerr << "The image " << fileLocation << "is not a valid image type!" << endl;
        return false;
    }

    //2. Create a new texture and load it from the specified image.
    Texture newText;
    if (!newText.loadFromImage(image)){
        return false;
    }

    //3. Put it into the texture map.
    if(!textures.insert(pair<string, Texture>(fileLocation, newText)).second){
        cerr << "The image " << fileLocation << " could not be inserted into the Asset Manager textures as "
        << fileLocation << " (It is likely already in there!)" << endl;
        return false;
    }

    return true;
}

bool AssetManager::exportImage(const Image& image, const string& fileLocation){
    //1. Alert the user that the image (if any) at the location will be overwritten.
    if (fs::exists(fileLocation)){
        cerr << "File at " << fileLocation << " already exists! Overwriting..." << endl;
    }

    //3. Create a file with the image.
    if (!image.saveToFile(fileLocation)){
        cerr << "Could not save image to " << fileLocation << "!" << endl;
        return false;
    }

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

    loadAll();

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

bool AssetManager::addFile(const string &fileLocation, int fileset){
    //1. Check if the file exists.
    if (!fs::exists(fileLocation)){
        cerr << "File at " << fileLocation << " does not exist!" << endl;
        return false;
    }

    //2. Add the file location to the set.
    if (validFile(fileLocation)){
        switch(fileset){
            case NORMAL:
                files.insert(fileLocation);
                break;

            case COMPRESSED:
                compressedFiles.insert(fileLocation);
                break;

            default:
                cerr << "Invalid fileset!" << endl;
                return false;
        }
    }

    else{
        cerr << "File " << fileLocation << " is not a valid image file!" << endl;
        return false;
    }

    return true;
}

bool AssetManager::addFolder(const string &folderLocation, int fileset){
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

            switch(fileset){
                case NORMAL:
                    if(files.insert(filePath).second){
                        numAdded++;
                    }
                    break;

                case COMPRESSED:
                    if(compressedFiles.insert(filePath).second){
                        numAdded++;
                    }
                    break;

                default:
                    cerr << "Invalid fileset!" << endl;
                    break;
            }
        }
    }

    cout << "Added " << numAdded << " files." << endl;

    return true;
}

bool AssetManager::delFile(const string& fileLocation, int fileset){
    switch(fileset){
        case NORMAL:{
            //1. Check if the file exists in the file set.
            if (files.count(fileLocation) == 0){
                cerr << "File " << fileLocation << " was not in the file list!" << endl;
                return false;
            }

            //2. Remove the file from the file set.
            files.erase(fileLocation);
            break;
        }

        case COMPRESSED:{
            //1. Check if the file exists in the file set.
            if (compressedFiles.count(fileLocation) == 0){
                cerr << "File " << fileLocation << " was not in the file list!" << endl;
                return false;
            }

            //2. Remove the file from the file set.
            compressedFiles.erase(fileLocation);
            break;
        }

        default:
            cerr << "Invalid fileset!" << endl;
    }

    return true;
}

bool AssetManager::delFolder(const string& folderLocation, int fileset) {
    //1. Check if the folder exists.
    if (!fs::exists(folderLocation)) {
        cerr << "The folder " << folderLocation << " does not exist!" << endl;
        return false;
    }

    //2. Make an iterator for the directory.
    auto iter = fs::directory_iterator(folderLocation);

    //3. For every file, try to erase it from the set if possible.
    unsigned int numRemoved = 0;
    switch (fileset) {
        case NORMAL: {
            for (const auto &file: iter) {
                if (files.erase(file.path().string()) == 1) {
                    numRemoved++;
                }
            }
            break;
        }

        case COMPRESSED: {
            for (const auto &file: iter) {
                if (compressedFiles.erase(file.path().string()) == 1) {
                    numRemoved++;
                }
            }
            break;
        }

        default:
            cerr << "Invalid fileset!" << endl;
            return false;
    }

    cout << "Removed " << numRemoved << " files." << endl;

    return true;
}

bool AssetManager::validFile(const string& fileLocation){
    //1. Take the filepath and isolate the extension.
    int dot = fileLocation.find_last_of('.');

    if (dot == string::npos){
        return false;
    }

    string extension = fileLocation.substr(dot, fileLocation.length() - dot);

    //2. Check the extension against those supported by the program and SFML.
    for (const string_view& i : FILE_EXTENSIONS){
        if (extension == i.data()){
            return true;
        }
    }

    return false;
}

set<string>& AssetManager::getFiles(){
    return files;
}

set<string>& AssetManager::getCompressedFiles(){
    return compressedFiles;
}

void AssetManager::listFiles(int fileset){
    //1. List the files in the file set.

    switch (fileset){
        case NORMAL:{
            cout << "Found " << files.size() << " files in the file list:" << endl;
            for (const string& file : files){
                cout << "- " << file << endl;
            }
            break;
        }

        case COMPRESSED:{
            cout << "Found " << compressedFiles.size() << " files in the compressed file list:" << endl;
            for (const string& file : compressedFiles){
                cout << "- " << file << endl;
            }
            break;
        }

        default:
            cerr << "Invalid Fileset!" << endl;
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

Image AssetManager::csvToImage(const string &fileLocation, const string& fileFormat) {
    ifstream file(fileLocation);
    istringstream parse;
    string rows, cols;
    unsigned long long size = 0;
    unsigned int rowN, colN;
    Image image;

    //Create missing texture if needed.
    if (textures.empty()){
        addTexture(MISSING_TEXTURE.data());
    }

    if (file.is_open()) {
        //1. Get first line which is the row and columns.
        string line;
        getline(file, line);

        //2. Parse the rows and columns and make the array of pixels.
        parse.str(line);
        parse >> rows;
        parse >> cols;

        try {
            colN = stoi(cols);
            rowN = stoi(rows);
            size = rowN * colN * 4;
        }

        catch (exception &exception) {
            cerr << "The rows and columns were not formatted correctly!"
                 << endl << "rows: " << rows << endl << "cols: " << cols << endl;
            return getTexture(MISSING_TEXTURE.data()).copyToImage();
        }

        auto* array = new sf::Uint8[size];

        //3. Parse the array and place each value in the array.
        getline(file, line);
        parse.clear();
        parse.str(line);

        unsigned int currPixel = 0;

        while (!parse.eof()) {
            string pixelString;
            sf::Uint8 pixelValue;

            parse >> pixelString;

            if (!pixelString.empty()) {
                try {
                    pixelValue = stoi(pixelString);
                }

                catch (std::exception &exception) {
                    cout << "currPixel: " << currPixel << endl;
                    cout << "pixelString:" << pixelString << "Here" << endl;
                }

                array[currPixel++] = pixelValue;
            }
        }

        image.create(rowN, colN, array);

        delete[] array;
        return image;
    }

    else{
        cerr << "File " << fileLocation << " does not exist! Returning missing texture..." << endl;
        return getTexture(MISSING_TEXTURE.data()).copyToImage();
    }
}

const string &AssetManager::getPrefix(){
    return prefix;
}

void AssetManager::setPrefix(const string &prefixIn){
    AssetManager::prefix = prefix;
}

const string& AssetManager::getOutputFolder(){
    return outputFolder;
}

void AssetManager::setOutputFolder(const string &outputFolder){
    AssetManager::outputFolder = outputFolder;
}

void AssetManager::setTextureFolder(const string &textureFolder){
    AssetManager::textureFolder = textureFolder;
}

bool AssetManager::isLoaded(){
    return loaded;
}