#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include "res/src/managers/AssetManager.h"
#include "res/src/managers/ViewManager.h"
#include "res/src/commands/Commands.h"
#include "res/src/python/PythonScript.h"

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

        sf::RenderWindow window(sf::VideoMode(1200, 800), "Media Compression by iCompression ~ TESTING MODE");
        window.setFramerateLimit(60); //Set the fps limit to 60 fps.
        AssetManager textureManager("../"); //Make a texture manager with the right prefix for CLion.
        AssetManager::loadAll();

        ViewManager viewManager(&window);
        ViewManager::addView("test", "../res/views/test.txt");
        ViewManager::addView("test2", "../res/views/test2.txt");

        ViewManager::getView("test").addButton("testButton", Vector2f(300, 50), "test.png", []()->void{
            ViewManager::changeView("test2");
            unique_ptr<ProgressBar>& david = ViewManager::getView("test").getProgressBar("david");
            david->setPercentage(david->getPercentage() + .05);
        });

        ViewManager::getView("test2").addButton("testButton2", Vector2f(300, 50), "test.png", []()->void{
            ViewManager::changeView("test");
        });

        ViewManager::getView("test2").getImage("image")->loadFromFile("../input/taipei 101.jpg");

        ViewManager::changeView("test");

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
                            ViewManager::activateElement(Mouse::getPosition(window));
                        }
                        break;
                    }
                }
            }
            ViewManager::getView("test").getText("mxv")->setString(std::to_string(Mouse::getPosition(window).x));
            ViewManager::getView("test").getText("myv")->setString(std::to_string(Mouse::getPosition(window).y));
            window.clear(sf::Color::White);
            ViewManager::drawAll();
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
                    exit(1);
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