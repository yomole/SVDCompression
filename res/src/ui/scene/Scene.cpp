#include "Scene.h"

Scene::Scene(){
    //1. Make null pointers to store in the maps for the getters.
    buttons.insert(pair<string, unique_ptr<Button>>("NULL", unique_ptr<Button>(nullptr)));
    progressBars.insert(pair<string, unique_ptr<ProgressBar>>("NULL", unique_ptr<ProgressBar>(nullptr)));
    texts.insert(pair<string, unique_ptr<Text>>("NULL", unique_ptr<Text>(nullptr)));
    images.insert(pair<string, unique_ptr<Sprite>>("NULL", unique_ptr<Sprite>(nullptr)));
    checkboxes.insert(pair<string, unique_ptr<Checkbox>>("NULL", unique_ptr<Checkbox>(nullptr)));
}

void Scene::parseArgs(istringstream &parse, vector<string> &args){
    while(!parse.eof()){
        //Load the first part of the string.
        string i, temp;
        parse >> i;

        //If the first character is a quotation mark, keep loading until last character is a quotation mark.
        if (i.front() == '\"'){
            //Remove beginning quotation mark.
            i.erase(0, 1);

            while(i.back() != '\"' && !parse.eof()){
                parse >> temp;
                i += (" " + temp);
            }

            //Remove ending quotation mark.
            i.erase(i.end() - 1);
        }

        //Parse special arguments.
        if (i == "_FILES_"){
            for (const string& file : AssetManager::getFiles()){
                args.push_back(file);
            }
        }

        else if (i == "_COMPRESSED FILES_"){
            for (const string& file : AssetManager::getCompressedFiles()){
                args.push_back(file);
            }
        }

        else{
            args.push_back(i);
        }
    }
}

void Scene::addButton(const string& elementName, const string& textureName, const Vector2f& position,
               const function<void()>& function){
    vector<string> v;
    auto* newButton = new Button(elementName, AssetManager::getTexture(textureName), position, function);
    this->buttons.insert(pair<string, Button*>(elementName, newButton));
}

void Scene::addText(const string& elementName, const Vector2f& position, const Font& font, unsigned int fontSize,
             const string& text){
    Text* newText;

    newText = new Text(text, font, fontSize);

    newText->setPosition(position);
    newText->setFillColor(Color::Black);

    //3. Create a new text object.
    this->texts.insert(pair<string, Text*>(elementName, newText));
}

void Scene::addImage(const string& elementName, const string& fileLocation, const Vector2f& position,
              const Vector2f& scale){
    try{
        auto* newImage = new Sprite;
            newImage->setTexture(AssetManager::getTexture(fs::path(fileLocation).filename().string()));
            newImage->setPosition(position);
            newImage->setScale(scale);
            this->images.insert(pair<string, Sprite*>(elementName, newImage));
    }

    catch(exception& exception){
        cerr << "Ran into an issue when creating image with name " << elementName;
    }
}

unordered_map<string, unique_ptr<Button>>& Scene::getButtons(){
    return buttons;
}

unordered_map<string, unique_ptr<Sprite>>& Scene::getImages(){
    return images;
}

unordered_map<string, unique_ptr<ProgressBar>>& Scene::getProgressBars(){
    return progressBars;
}

unordered_map<string, unique_ptr<Text>>& Scene::getTexts(){
    return texts;
}

unordered_map<string, unique_ptr<Checkbox>>& Scene::getCheckboxes(){
    return checkboxes;
}

unique_ptr<Button>& Scene::getButtons(const string &elementName){
    if (buttons.count(elementName) != 0){
        return buttons.at(elementName);
    }
    else{
        return buttons.at("NULL");
    }
}

unique_ptr<Sprite>& Scene::getImages(const string &elementName){
    if (images.count(elementName) != 0){
        return images.at(elementName);
    }
    else{
        return images.at("NULL");
    }
}

unique_ptr<ProgressBar>& Scene::getProgressBars(const string &elementName){
    if (progressBars.count(elementName) != 0){
        return progressBars.at(elementName);
    }
    else{
        return progressBars.at("NULL");
    }
}

unique_ptr<Text> &Scene::getTexts(const string &elementName){
    if (texts.count(elementName) != 0){
        return texts.at(elementName);
    }
    else{
        return texts.at("NULL");
    }
}

unique_ptr<Checkbox> &Scene::getCheckboxes(const string &elementName){
    if (checkboxes.count(elementName) != 0){
        return checkboxes.at(elementName);
    }
    else{
        return checkboxes.at("NULL");
    }
}