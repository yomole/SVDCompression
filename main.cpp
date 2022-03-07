#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#include "res/scripts/managers/AssetManager.h"
#include "res/scripts/managers/UIElementManager.h"
#include "res/scripts/ui/Button.h"
#include "res/scripts/ui/TextBased.h"

using namespace std;
using sf::Event;
using sf::Mouse;
using std::rand;

int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 600), "Media Compression by iCompression ");
    window.setFramerateLimit(60); //Set the fps limit to 60 fps.
    AssetManager textureManager("../"); //Make a texture manager with the right prefix for CLion.
    UIElementManager uiElementManager(&window);

    AssetManager::addTexture("test.png");
    AssetManager::addTexture("testPressed.png");
    AssetManager::addFont("OpenSans-Regular400-Italics.ttf");

    Button button("Dr. Disco", AssetManager::getTexture("test.png"), Vector2f(0, 0), [&button]()->void{
        cout << button.getName() << " is changing colors!" << endl;
        button.getSprite().setColor(sf::Color(rand()%256, rand()%256, rand()%256));
    });

    Button button2("Press button test", AssetManager::getTexture("test.png"), Vector2f(256, 256), [&button2]()->void{
        button2.setTexture(AssetManager::getTexture("testPressed.png"));
    });

    Button button3("Missing texture test", AssetManager::getTexture("test2.png"), Vector2f(128, 0), [&button3]()->void{
        button3.getSprite().setTexture(AssetManager::getTexture("tested.png"));
    });

    TextBased testText("testing text", Vector2f(40, 150), AssetManager::getFont(DEFAULT_FONT), "Hello World!");

    UIElementManager::addElement(&button);
    UIElementManager::addElement(&button2);
    UIElementManager::addElement(&button3);
    UIElementManager::addElement(&testText);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch(event.type){
                case(Event::Closed):{
                    window.close();
                    break;
                }

                case(Event::MouseButtonPressed):{
                    if (event.mouseButton.button == Mouse::Left){
                        UIElementManager::activateElement(Mouse::getPosition(window));
                    }
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        UIElementManager::drawAll();
        window.display();
    }

    return 0;
}
