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

//FUNCTION PROTOTYPES:
bool isCommand(const string& command, const vector<string>& args, const string& target);

int main(int argc, char* argv[]) {

    //Testing...
    if (argc != 0 && string(argv[1]) == "-test") {

        sf::RenderWindow window(sf::VideoMode(1200, 600), "Media Compression by iCompression ~ TESTING MODE");
        window.setFramerateLimit(60); //Set the fps limit to 60 fps.
        AssetManager textureManager("../"); //Make a texture manager with the right prefix for CLion.
        UIElementManager uiElementManager(&window);

        AssetManager::loadAll();

        ProgressBar *progress = new ProgressBar("Progress Bar Test", Vector2f(200, 20), Vector2f(300, 200));

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

        TextBased testText("testing text", Vector2f(40, 150), AssetManager::getFont(DEFAULT_FONT), "Hello World!");

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
    else if (argc != 0 && string(argv[1]) == "-cli"){
        cout << "Media Compression by iCompression: CLI Mode" << endl;
        string line, command;
        do{
            command = "";
            //1. Get the entire line of command.
            getline(cin, line);

            //2. Parse it into command parts.
            istringstream parse(line);
            vector<string> args;
            parse >> command;
            while(!parse.eof()){
                string i;
                parse >> i;
                args.push_back(i);
            }

            //3. Run the appropriate command.
            if (isCommand(command, args, "add")){
                if (command == "help"){
                    getHelp(ADD);
                }
                else{

                }
            }

            else if (isCommand(command, args, "del")){
                if (command == "help"){
                    getHelp(DEL);
                }
                else{

                }
            }

            else if (isCommand(command, args, "python")){
                if (command == "help"){
                    getHelp(PYTHON);
                }
                else{
                    runPy(args.at(0));
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