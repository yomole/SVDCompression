#include "ButtonFunctions.h"

void VOID::operator()(const vector<string> &nameAndArgs){
    cerr << "Button has no function associated!" << endl;
}

void ChangeScene::operator()(const vector<string>& nameAndArgs){
    try {
        SceneManager::changeScene(nameAndArgs.at(1));
    }
    catch(out_of_range& outOfRange){
        cerr << "No scene argument for function ChangeScene!" << endl;
        return;
    }
}

void ChangeImage::operator()(const vector<string> &nameAndArgs){
    try {
        string viewName = nameAndArgs.at(1);
        string imageName = nameAndArgs.at(2);
        string newImageName = nameAndArgs.at(3);
    }
    catch(out_of_range& outOfRange){
        cerr << "One or more arguments do not exist for function ChangeImage!" << endl;
    }

    if (!AssetManager::textureExists(nameAndArgs.at(4))){
        if (!(AssetManager::addImage(nameAndArgs.at(4)))){
            return;
        }
    }

    SceneManager::getScene(nameAndArgs.at(1)).getImages(nameAndArgs.at(2))->setTexture(AssetManager::getTexture(nameAndArgs.at(3)), true);
}

void CycleImagesFwd::operator()(vector<string>& nameAndArgs){
    const unsigned int firstImage = 5;
    string sceneName = nameAndArgs.at(1);
    string imageName = nameAndArgs.at(2);
    string linkedButton = nameAndArgs.at(3);
    string currString = nameAndArgs.at(4);

    unsigned int curr,currImage;
    try {
        curr = stoi(currString) + 1;
        currImage = curr + firstImage;
    }

    catch(invalid_argument& invalidArgument){
        cerr << "Argument for starting image is not in a valid format! Currently: " << currString << endl;
    }

    catch(out_of_range& outOfRange){
        cerr << "Argument for starting image is too big! Currently: " << currString << endl;
    }

    if (currImage >= nameAndArgs.size()){
        curr = 0;
        currImage = curr + firstImage;
    }

    SceneManager::getScene(sceneName).getTexts("count")->setString("Current: " + to_string(curr));

    string fileLocation = nameAndArgs.at(currImage);
    string fileName = fs::path(fileLocation).filename().string();

    if (!AssetManager::textureExists(fileName)) {
        if (!(AssetManager::addImage(fileLocation))) {
            return;
        }
    }
    SceneManager::getScene(sceneName).getImages(imageName)->setTexture(
                AssetManager::getTexture(fileName), true);

    string currentValue = to_string(curr);
    nameAndArgs.at(4) = currentValue;
    SceneManager::getScene(sceneName).getButtons(linkedButton)->getArguments().at(4) = currentValue;
}

void CycleImagesRev::operator()(vector<string> &nameAndArgs){
    const unsigned int firstImage = 5;
    string sceneName = nameAndArgs.at(1);
    string imageName = nameAndArgs.at(2);
    string linkedButton = nameAndArgs.at(3);
    string currString = nameAndArgs.at(4);

    unsigned int curr,currImage;
    try {
        curr = stoi(currString) - 1;
        currImage = curr + firstImage;
    }

    catch(invalid_argument& invalidArgument){
        cerr << "Argument for starting image is not in a valid format! Currently: " << currString << endl;
    }

    catch(out_of_range& outOfRange){
        cerr << "Argument for starting image is too big! Currently: " << currString << endl;
    }

    if (currImage < firstImage){
        curr = nameAndArgs.size() - 1 - firstImage;
        currImage = curr + firstImage;
    }

    SceneManager::getScene(sceneName).getTexts("count")->setString("Current: " + to_string(curr));

    string fileLocation = nameAndArgs.at(currImage);
    string fileName = fs::path(fileLocation).filename().string();

    if (!AssetManager::textureExists(fileName)) {
        if (!(AssetManager::addImage(fileLocation))) {
            return;
        }
    }
    SceneManager::getScene(sceneName).getImages(imageName)->setTexture(
            AssetManager::getTexture(fileName), true);

    string currentValue = to_string(curr);
    nameAndArgs.at(4) = currentValue;
    SceneManager::getScene(sceneName).getButtons(linkedButton)->getArguments().at(4) = currentValue;
}

void Compress::operator()(vector<string> &nameAndArgs) {
    string sizeString;
    try{
        sizeString = nameAndArgs.at(1);
    }
    catch(out_of_range& outOfRange){
        cerr << "No size argument for function Compress!" << endl;
        return;
    }

    SVDAlgorithm(sizeString, AssetManager::getFiles(), AssetManager::getPrefix() + "res/python/SVD.py");
}

function<void(vector<string>&)> getFunction(vector<string>& nameAndArgs){
    string functionName = nameAndArgs.at(0);

    if(functionName == "ChangeScene"){
        return function<void(const vector<string>&)>(ChangeScene{});
    }

    else if (functionName == "ChangeImage"){
        return function<void(const vector<string>&)>(ChangeImage{});
    }

    else if (functionName == "CycleImagesFwd"){
        return function<void(vector<string>&)>(CycleImagesFwd{});
    }

    else if (functionName == "CycleImagesRev"){
        return function<void(vector<string>&)>(CycleImagesRev{});
    }

    else{
        return function<void(const vector<string>&)>(VOID{});
    }
}
