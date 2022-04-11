#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include "res/scripts/managers/AssetManager.h"
#include "res/scripts/managers/UIElementManager.h"
#include "res/scripts/ui/Button.h"
#include "res/scripts/ui/super/TextBased.h"
#include "res/scripts/ui/ProgressBar.h"
#include "res/scripts/commands/Commands.h"
#include "res/scripts/python/PythonScript.h"

using sf::Event;
using sf::Mouse;
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

int main(int argc, char* argv[]) {

    //Testing...
    if (argc > 1 && string(argv[1]) == "-test") {

        sf::RenderWindow window(sf::VideoMode(1200, 600), "Media Compression by iCompression ~ TESTING MODE");
        window.setFramerateLimit(60); //Set the fps limit to 60 fps.
        AssetManager textureManager("../"); //Make a texture manager with the right prefix for CLion.
        UIElementManager uiElementManager(&window);

        AssetManager::loadAll();

        //TODO: Make progress bar entities part of the asset manager to avoid memory leaks!
        auto *progress = new ProgressBar("Progress Bar Test", Vector2f(200, 20), Vector2f(300, 200));

        Button button("Dr. Disco", AssetManager::getTexture("test.png"), Vector2f(0, 0),
                      [&button, &progress]() -> void {
                          button.getSprite().setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                          cout << "Progress bar ( " << &(*progress) << ") percentage went from "
                               << progress->getPercentage();
                          progress->setPercentage(progress->getPercentage() + .05);
                          cout << " to " << progress->getPercentage() << endl;
                      });

        Button button2("Press button test", AssetManager::getTexture("test.png"), Vector2f(256, 256),
                       [&button2]() -> void {
                           button2.getSprite().setTexture(AssetManager::getTexture("testPressed.png"));
                       });

        Button button3("Missing texture test", AssetManager::getTexture("test2.png"), Vector2f(128, 0),
                       [&button3]() -> void {
                           button3.getSprite().setTexture(AssetManager::getTexture("tested.png"));
                       });

        TextBased testText("testing text", Vector2f(40, 150), AssetManager::getFont(DEFAULT_FONT.data()), "Hello World!");

        UIElementManager::addElement(&button);
        UIElementManager::addElement(&button2);
        UIElementManager::addElement(&button3);
        UIElementManager::addElement(&testText);

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case (Event::Closed): {
                        window.close();
                        break;
                    }

                    case (Event::MouseButtonPressed): {
                        if (event.mouseButton.button == Mouse::Left) {
                            UIElementManager::activateElement(Mouse::getPosition(window));
                        }
                        break;
                    }
                }
            }

            window.clear(sf::Color::White);
            UIElementManager::drawAll();

            for (RectangleShape *i: progress->getShapes()) {
                window.draw(*i);
            }

            window.display();
        }
        return 0;
    }

    //CLI Mode (Prioritize first for basic testing).
    else if (argc > 1 && string(argv[1]) == "-cli"){
        cout << "Media Compression by iCompression: CLI Mode" << endl;
        ifstream file;

        if (argc > 2 && string(argv[2]) == "-file"){
            file.open(argv[3]);
        }

        string line, command;
        do{
            command = "";
            if (argc <= 2) {
                //1. Get the entire line of command.
                getline(cin, line);
            }
            else{
                if (file.is_open()){
                    getline(file, line);
                }
                else{
                    cerr << "file at " << argv[3] << " does not exist!";
                }
            }

            //2. Parse it into command parts.
            istringstream parse(line);
            vector<string> args;
            parse >> command;
            parseArgs(parse, args);

            //3. Run the appropriate command.
            if (isCommand(command, args, "add")){
                if (command == "help"){
                    getHelp(ADD);
                }
                else{
                    AssetManager::addFile(args.at(0));
                }
            }

            else if (isCommand(command, args, "rm")){
                if (command == "help"){
                    getHelp(RM);
                }
                else{
                    AssetManager::delFile(args.at(0));
                }
            }

            else if (isCommand(command, args, "ls")){
                if (command == "help"){
                    getHelp(LS);
                }
                else{
                    AssetManager::listFiles();
                }
            }

            else if (isCommand(command, args, "python")){
                if (command == "help"){
                    getHelp(PYTHON);
                }
                else{
                    runPy(args.at(0), AssetManager::getFiles());
                }
            }

            else if (isCommand(command, args, "about")){
                if (command == "help"){
                    getHelp(ABOUT);
                }
                else{
                    printAbout();
                }
            }

            else if (isCommand(command, args, "help")){
                getHelp(HELP);
            }

            //Display all commands that are available along with their breakdown.
            else{
                if (command != "exit"){
                    listCommands();
                }
            }

        } while (command != "exit");


    }

    //The SFML Application.
    else{

    }
}

bool isCommand(const string& command, const vector<string>& args, const string& target){
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
    ifstream file("../README.md");

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