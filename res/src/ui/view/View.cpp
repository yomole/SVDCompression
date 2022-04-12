#include "View.h"

View::View(const string &fileLocation){
    //1. Make null pointers to store in the maps for the getters.
    buttons.insert(pair<string, unique_ptr<Button>>("NULL", unique_ptr<Button>(nullptr)));
    progressBars.insert(pair<string, unique_ptr<ProgressBar>>("NULL", unique_ptr<ProgressBar>(nullptr)));
    texts.insert(pair<string, unique_ptr<Text>>("NULL", unique_ptr<Text>(nullptr)));
    images.insert(pair<string, unique_ptr<Texture>>("NULL", unique_ptr<Texture>(nullptr)));

    //2. Create the different elements (besides buttons and checkboxes) using the file.
    serialize(fileLocation);
}

void View::serialize(const string &fileLocation){
    //1. Give the name of the view (isolate the filename).
    int substring = fileLocation.find_last_of('.') - fileLocation.find_last_of('/') - 1;
    this->name = fileLocation.substr(fileLocation.find_last_of('/') + 1, substring);

    //2. Create the filestream object and open it.
    ifstream file(fileLocation);

    if (file.is_open()){
        string line;
        unsigned int linenum = 1;
        //3. Get the line and parse it.
        while(getline(file, line)){
            //Parse the element and find it in the list.
            istringstream parse(line);
            string element;

            parse >> element;

            //Comment in the view starts with '#'
            if (element.front() == '#' || element.empty()){
                continue;
            }

            else if (element == "progressBar"){
                addProgressBar(parse);
            }

            else if (element == "text"){
                addText(parse);
            }

            else if(element == "image"){
                addImage(parse);
            }

            else{
                cerr << "Syntax error in line " << linenum << " of file " << fileLocation << "! Skipping...";
            }

            linenum++;
        }
    }

    else{
        cerr << "View from " << fileLocation << " could not be loaded!";
        exit(1);
    }
}

void View::addButton(const string& elementName, Vector2f position, const string& textureName, const function<void()>& function){
    auto* newButton = new Button(elementName, AssetManager::getTexture(textureName), position, function);
    this->buttons.insert(pair<string, Button*>(elementName, newButton));
}

void View::addProgressBar(istringstream& parse){
    string elementName, xsize, ysize, xpos, ypos;
    try{
        //1. Parse all of the relevant info.
        parse >> elementName;
        parse >> xpos;
        parse >> ypos;
        parse >> xsize;
        parse >> ysize;

        //2. Convert size and position to Vector2fs
        Vector2f size(stof(xsize), stof(ysize));
        Vector2f position(stof(xpos), stof(ypos));

        //3. Create a new progress bar.
        auto* progressBar = new ProgressBar(elementName, size, position);
        this->progressBars.insert(pair<string, ProgressBar*>(elementName, progressBar));
    }

    catch(exception& exception){
        cerr << "Ran into an issue when creating progress bar with name " << elementName;
    }
}

void View::addText(istringstream& parse){
    string elementName, xpos, ypos, font, fontS, text;

    try{
        //1. Parse all of the relevant info.
        parse >> elementName;
        parse >> xpos;
        parse >> ypos;
        parse >> font;
        parse >> fontS;
        while(!parse.eof()){
            string i;
            parse >> i;
            text += i + " ";
        }

        //2. Convert position to vector 2f, get the font from asset manager, and convert the font size to an unsigned int.
        Vector2f position(stof(xpos), stof(ypos));
        unsigned int fontSize = stoi(fontS);
        Text* newText;

        if (font == "default"){
            newText = new Text(text, AssetManager::getFont(DEFAULT_FONT.data()), fontSize);
        }
        else{
            newText = new Text(text, AssetManager::getFont(font), fontSize);
        }

        newText->setPosition(position);
        newText->setFillColor(Color::Black);

        //3. Create a new text object.
        this->texts.insert(pair<string, Text*>(elementName, newText));
    }

    catch(exception& exception){
        cerr << "Ran into an issue when creating text with name " << elementName;
    }
}

void View::addImage(istringstream& parse){
    string elementName;
    parse >> elementName;

    try{
        auto* newTexture = new Texture();
        this->images.insert(pair<string, Texture*>(elementName, newTexture));
    }

    catch(exception& exception){
        cerr << "Ran into an issue when creating image with name " << elementName;
    }
}

unordered_map<string, unique_ptr<Button>>& View::getButtons(){
    return buttons;
}

unordered_map<string, unique_ptr<Texture>>& View::getImages(){
    return images;
}

unordered_map<string, unique_ptr<ProgressBar>>& View::getProgressBars(){
    return progressBars;
}

unordered_map<string, unique_ptr<Text>>& View::getTexts(){
    return texts;
}

unique_ptr<Button>& View::getButton(const string &elementName){
    if (buttons.count(elementName) != 0){
        return buttons.at(elementName);
    }
    else{
        return buttons.at("NULL");
    }
}

unique_ptr<Texture> &View::getImage(const string &elementName){
    if (images.count(elementName) != 0){
        return images.at(elementName);
    }
    else{
        return images.at("NULL");
    }
}

unique_ptr<ProgressBar> &View::getProgressBar(const string &elementName){
    if (progressBars.count(elementName) != 0){
        return progressBars.at(elementName);
    }
    else{
        return progressBars.at("NULL");
    }
}

unique_ptr<Text> &View::getText(const string &elementName){
    if (texts.count(elementName) != 0){
        return texts.at(elementName);
    }
    else{
        return texts.at("NULL");
    }
}