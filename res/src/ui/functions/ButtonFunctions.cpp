#include "ButtonFunctions.h"

void VOID::operator()(const vector<string> &nameAndArgs){
    cerr << "Button has no function associated!" << endl;
}

void ChangeScene::operator()(const vector<string>& nameAndArgs){
    SceneManager::changeView(nameAndArgs.at(1));
}

void ChangeImage::operator()(const vector<string> &nameAndArgs){
    if (!AssetManager::textureExists(nameAndArgs.at(4))){
        if (!(AssetManager::addImage(nameAndArgs.at(4)))){
            return;
        }
    }

    SceneManager::getView(nameAndArgs.at(1)).getImages(nameAndArgs.at(2))->setTexture(AssetManager::getTexture(nameAndArgs.at(3)), true);
}

void CycleImages::operator()(vector<string>& nameAndArgs){
    string sceneName = nameAndArgs.at(1);
    string imageName = nameAndArgs.at(2);
    unsigned int curr;
    try {
        curr = stoi(nameAndArgs.at(3));
    }

    catch(invalid_argument& invalidArgument){
        cerr << "Argument for starting image is not in a valid format!" << endl;
    }

    catch(out_of_range& outOfRange){
        cerr << "Argument for starting image is too big!" << endl;
    }

    if (curr + 5 >= nameAndArgs.size()){
        curr = 0;
    }

    if (curr + 5 < nameAndArgs.size()){
        cout << SceneManager::getView(sceneName).getImages(imageName)->getPosition().x << " ";
        cout << SceneManager::getView(sceneName).getImages(imageName)->getPosition().y << endl;
        if (!AssetManager::textureExists(nameAndArgs.at(curr + 5 + 1))){
            if (!(AssetManager::addImage(nameAndArgs.at(curr + 5)))){
                return;
            }
        }
        SceneManager::getView(sceneName).getImages(imageName)->setTexture(AssetManager::getTexture(nameAndArgs.at(curr + 5 + 1)), true);
        curr+=2;
    }

    string currentValue = to_string(curr);
    nameAndArgs.at(3) = currentValue;

}

function<void(vector<string>&)> getFunction(vector<string>& nameAndArgs){
    if(nameAndArgs.at(0) == "ChangeScene"){
        return function<void(const vector<string>&)>(ChangeScene{});
    }

    else if (nameAndArgs.at(0) == "ChangeImage"){
        return function<void(const vector<string>&)>(ChangeImage{});
    }

    else if (nameAndArgs.at(0) == "CycleImages"){
        return function<void(vector<string>&)>(CycleImages{});
    }

    else{
        return function<void(const vector<string>&)>(VOID{});
    }
}