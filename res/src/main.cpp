#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include <csignal>
#include "managers/AssetManager.h"
#include "managers/SceneManager.h"
#include "commands/Commands.h"
#include "python/PythonScript.h"

using sf::Event;
using sf::Mouse;
using sf::Vector2u;
using std::cin;
using std::cout;
using std::string;
using std::rand;
using std::getline;
using std::istringstream;
using std::vector;
using std::ifstream;

//FUNCTION PROTOTYPES:
bool isCommand(const string& command, const vector<string>& args, const string& target);
void parseArgs(istringstream& parse, vector<string>& args);
void printAbout();
string getPrefix();
void showImage(const string& fileLocation);
void showImages();
void adjustWindow(sf::RenderWindow& window, unique_ptr<Sprite>& original, unique_ptr<Sprite>& compressed,
                  unique_ptr<Button>& forward, unique_ptr<Button>& reverse);

//CONSTANTS:
const float VIDEOMODE_SCALE = 2;
const unsigned int IMAGE_MARGIN = 8;

int main(int argc, char* argv[]) {

    cout << "Starting directory is: " << (getPrefix().empty() ? "SVDCompression\\" : "SVDCompression\\bin") << endl;

    //Load the python interpreter to keep it alive for as long as possible.
    scope = new py::scoped_interpreter{};

    cout << "Media Compression by iCompression: CLI Mode" << endl;
    ifstream file;

    if (argc > 2 && string(argv[2]) == "-file") {
        file.open(argv[3]);
    }

    string line, command;

    //Modified https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
    signal(SIGINT, [](int signum) -> void { exit(signum); });
    do {
        command = "";
        if (argc <= 2) {
            cout << "SVDCompression> ";
            //1. Get the entire line of command.
            getline(cin, line);
        } else {
            if (file.is_open()) {
                getline(file, line);
            } else {
                cerr << "file at " << argv[3] << " does not exist!";
                exit(1);
            }
        }

        //2. Parse it into command parts.
        istringstream parse(line);
        vector<string> args;
        parse >> command;
        parseArgs(parse, args);

        cout << endl;

        //3. Run the appropriate command.
        if (isCommand(command, args, "add")) {
            if (command == "help" || args.size() != 1) {
                getHelp(ADD);
            } else if (args.size() == 1) {
                AssetManager::addFile(args.at(0));
            }
        } else if (isCommand(command, args, "addf")) {
            if (command == "help" || args.size() != 1) {
                getHelp(ADDF);
            } else if (args.size() == 1) {
                AssetManager::addFolder(args.at(0));
            }
        } else if (isCommand(command, args, "rm")) {
            if (command == "help" || args.size() != 1) {
                getHelp(RM);
            } else if (args.size() == 1) {
                AssetManager::delFile(args.at(0));
            }
        } else if (isCommand(command, args, "rmf")) {
            if (command == "help" || args.size() != 1) {
                getHelp(RMF);
            } else if (args.size() == 1) {
                AssetManager::delFolder(args.at(0));
            }
        } else if (isCommand(command, args, "ls")) {
            if (command == "help") {
                getHelp(LS);
            } else {
                AssetManager::listFiles();
            }
        } else if (isCommand(command, args, "compress")) {
            if (command == "help" || args.size() != 1) {
                getHelp(COMPRESS);
            } else if (args.size() == 1) {
                SVDAlgorithm(args.at(0), AssetManager::getFiles(), AssetManager::getPrefix() + "res/python/SVD.py");
            }
        } else if (isCommand(command, args, "export")) {
            if (command == "help" || args.size() != 1) {
                getHelp(EXPORT);
            } else if (args.size() == 1) {
                AssetManager::csvToImage(AssetManager::getPrefix() + "output/testOutput.txt", args.at(0));
            }
        } else if (isCommand(command, args, "show")) {
            if (command == "help" || args.size() != 1) {
                getHelp(SHOW);
            } else if (args.size() == 1 && args.at(0) != "all") {
                showImage(args.at(0));
            } else{
                showImages();
            }
        } else if (isCommand(command, args, "about")) {
            if (command == "help") {
                getHelp(ABOUT);
            } else {
                printAbout();
            }
        } else if (isCommand(command, args, "help")) {
            getHelp(HELP);
        }

        //Display all commands that are available along with their breakdown.
        else {
            if (command != "exit") {
                listCommands();
            }
        }

        cout << endl;

    } while (command != "exit");

    //Close the python interpreter.
    delete scope;

}

bool isCommand(const string& command, const vector<string>& args, const string& target){
    //1. Check that the command is correct and that
    return ((command == target) || (!args.empty() && args.at(0) == target));
}

void parseArgs(istringstream& parse, vector<string>& args){
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

        args.push_back(i);
    }
}

void printAbout(){
    //1. Get the readme file and pipe to CLI output line by line.
    ifstream file("README.md");

    if (file.is_open()){
        string line;
        while(getline(file, line)){
            cout << line << endl;
        }
    }
    else{
        cerr << "Unable to display information about the program. For information, please go to the github repository.";
    }
}

string getPrefix(){
    //1. Determine the current filepath. If bin, prefix is ../. If it is SVDCompression, it is nothing. Else, error.
    string currDir = fs::current_path().filename().string();

    if (currDir == "bin"){
        return "../";
    }

    else if (currDir == "SVDCompression"){
        return "";
    }

    else{
        cerr << "The executable's location or shortcut working directory is not correct!" << endl;
        exit(1);
    }
}

void showImage(const string& fileLocation){
    //1. Check if the file exists and is a valid image file.
    if (fs::exists(fileLocation) && AssetManager::validFile(fileLocation)){
        //2. Alert the user that the image will be displayed and they will be required to close window.
        cout << "Displaying " << fileLocation << "." << endl << "Close the window to continue..." << endl;
        //3. Load texture, assign to sprite, and generate scaling factor for sprite.
        Texture image;
        image.loadFromFile(fileLocation);
        Sprite dispImage(image);
        float scaleX = ((float)sf::VideoMode::getDesktopMode().width / VIDEOMODE_SCALE) / (float)image.getSize().x;
        float scaleY = ((float)sf::VideoMode::getDesktopMode().height / VIDEOMODE_SCALE) / (float)image.getSize().y;

        Vector2f scales;

        //5. Use the smaller of the two possible scaling factors (in case longer than tall or vice versa).
        if (scaleX < scaleY){
            scales.x = scaleX;
            scales.y = scaleX;
        }

        else{
            scales.x = scaleY;
            scales.y = scaleY;
        }

        //6. Set scale and display image.
        dispImage.setScale(scales);
        sf::RenderWindow window(sf::VideoMode(dispImage.getGlobalBounds().width, dispImage.getGlobalBounds().height),
                                "Media Compression by iCompression ~ show " + fileLocation, sf::Style::Close);
        AssetManager("");
        while(window.isOpen()) {
            Event event{};
            while (window.pollEvent(event)) {

                if (event.type == Event::Closed) {
                    window.close();
                }
                window.draw(dispImage);
                window.display();
            }
        }
    }

    else{
        cerr << "File " << fileLocation << " does not exist or isn't valid, so the image cannot be displayed." << endl;
    }
}

void showImages(){
        //2. Alert the user that the images will be displayed and they will be required to close window.
        cout << "Displaying compressed images." << endl << "Close the window to continue..." << endl;

        //3. Create the window and scene manager. Add the scene and change to it.
        sf::RenderWindow window(sf::VideoMode(0, 0),
                                "Media Compression by iCompression: Qualitative Comparison", sf::Style::Close);
        window.setFramerateLimit(60);
        AssetManager("");
        SceneManager sceneManager(&window);
        SceneManager::addScene("Images");
        SceneManager::changeScene("Images");

        //4. Load all of the images.
        auto& originalSet = AssetManager::getFiles();
        //TODO: Replace with compressedFiles once SVD is finished.

        for (auto& file : originalSet){
            AssetManager::addFile(file, COMPRESSED);
        }

        auto& compressedSet = AssetManager::getCompressedFiles();

        auto originalImages = originalSet.begin();
        auto compressedImages = compressedSet.begin();

        for (auto& file : originalSet){
            if (!AssetManager::textureExists(file)){
                AssetManager::addImage(AssetManager::getPrefix() + file);
            }
        }

        //4. Create the buttons and sprites to be moved later.
        Scene& scene = SceneManager::getScene("Images");
        scene.addImage("original", *originalImages, Vector2f(0,0));
        scene.addImage("compressed", *originalImages, Vector2f(0,0));

        auto& original = scene.getImages("original");
        auto& compressed = scene.getImages("compressed");

        scene.addButton("forward", "Forward.png", Vector2f(0,0), [&originalImages, &compressedImages, &originalSet,
                                                                  &compressedSet, &original, &compressed, &window, &scene]()->void {
            //Check if the iterator will reach the end, and reset to the beginning if true.
            originalImages++;
            compressedImages++;
            if (originalImages == originalSet.end()) {
                originalImages = originalSet.begin();
                compressedImages = compressedSet.begin();
            }

            //Get the next textures.
            const Texture &originalNext = AssetManager::getTexture(fs::path(*originalImages).filename().string());
            const Texture &compressedNext = AssetManager::getTexture(fs::path(*compressedImages).filename().string());

            //Set the images textures to the next textures.
            original->setTexture(originalNext, true);
            compressed->setTexture(compressedNext, true);

            //Adjust the window to fit the new images.
            adjustWindow(window, scene.getImages("original"), scene.getImages("compressed"),
                         scene.getButtons("forward"),
                         scene.getButtons("reverse"));
        });

        scene.addButton("reverse", "Reverse.png", Vector2f(0,0), [&originalImages, &compressedImages, &originalSet,
                                                                  &compressedSet, &original, &compressed, &window, &scene]()->void {
            //Check if the iterator is at the beginning. If so, wrap around to the end - 1.
            originalImages--;
            compressedImages--;
            if (originalImages == originalSet.begin()) {
                originalImages = --originalSet.end();
                compressedImages = --compressedSet.end();
            }

            //Get the previous textures.
            const Texture &originalPrev = AssetManager::getTexture(fs::path(*originalImages).filename().string());
            const Texture &compressedPrev = AssetManager::getTexture(fs::path(*compressedImages).filename().string());

            //Set the images textures to the previous textures.
            original->setTexture(originalPrev, true);
            compressed->setTexture(compressedPrev, true);

            //Adjust the window to fit the new images.
            adjustWindow(window, scene.getImages("original"), scene.getImages("compressed"),
                         scene.getButtons("forward"),
                         scene.getButtons("reverse"));
        });

        auto& forward = scene.getButtons("forward");
        auto& reverse = scene.getButtons("reverse");

        //Adjust the window first before opening it.
        adjustWindow(window, original, compressed, forward, reverse);

        while(window.isOpen()) {
            Event event{};
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                else if (event.type == Event::MouseButtonPressed){
                    if (event.mouseButton.button == Mouse::Left){
                        SceneManager::activateElement(Mouse::getPosition(window));
                    }
                }

                window.clear(Color::White);
                SceneManager::drawAll();
                window.display();
            }
        }
}

void adjustWindow(sf::RenderWindow& window, unique_ptr<Sprite>& original, unique_ptr<Sprite>& compressed,
                  unique_ptr<Button>& forward, unique_ptr<Button>& reverse){
    //1. Get the images and their size.
    sf::Vector2u size2u = original->getTexture()->getSize();

    //2. Generate the scaling factor for the images.
    float scaleX = ((float)sf::VideoMode::getDesktopMode().width / VIDEOMODE_SCALE) / (float)size2u.x;
    float scaleY = ((float)sf::VideoMode::getDesktopMode().height / VIDEOMODE_SCALE) / (float)size2u.y;

    //3. Use the smaller of the two.
    Vector2f scales;
    scales = (scaleX < scaleY ? Vector2f(scaleX, scaleX) : Vector2f(scaleY, scaleY));
    original->setScale(scales);
    compressed->setScale(scales);

    //4. Resize the window to fit both images, buttons, and text with margins.
    Vector2u buttonSize = forward->getBaseTexture().getSize();
    unsigned int imageWidth = original->getGlobalBounds().width;
    unsigned int imageHeight = original->getGlobalBounds().height;

    unsigned int width = (imageWidth * 2) + (3 * IMAGE_MARGIN);
    unsigned int height = imageHeight + (2 * IMAGE_MARGIN) + buttonSize.x;

    Vector2u newSize(width, height);
    window.setSize(newSize);
    window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
    window.setPosition(sf::Vector2i(0,0));

    //5. Reposition the elements.
    original->setPosition(Vector2f(IMAGE_MARGIN, IMAGE_MARGIN));
    compressed->setPosition(Vector2f(((2 * IMAGE_MARGIN) + imageWidth), IMAGE_MARGIN));
    forward->getSprite().setPosition(Vector2f(IMAGE_MARGIN + buttonSize.x, (2 * IMAGE_MARGIN) + imageHeight));
    reverse->getSprite().setPosition(Vector2f(IMAGE_MARGIN, (2 * IMAGE_MARGIN) + imageHeight));
}