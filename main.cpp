#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#include "res/scripts/managers/TextureManager.h"
#include "res/scripts/managers/UIElementManager.h"
#include "res/scripts/ui/Button.h"

using namespace std;
using sf::Event;
using sf::Mouse;
using std::rand;

int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 600), "Media Compression by iCompression ");
    window.setFramerateLimit(60); //Set the fps limit to 60 fps.
    TextureManager textureManager("../"); //Make a texture manager with the right prefix for CLion.
    UIElementManager uiElementManager(&window);

    TextureManager::addTexture("test.png");
    TextureManager::addTexture("testPressed.png");

    Button button("Dr. Disco", TextureManager::getTexture("test.png"), Vector2f(0,0), [&button]()->void{
        cout << button.getName() << " is changing colors!" << endl;
        button.getSprite().setColor(sf::Color(rand()%256, rand()%256, rand()%256));
    });

    Button button2("Press button test", TextureManager::getTexture("test.png"), Vector2f(256, 256), [&button2]()->void{
        button2.setTexture(TextureManager::getTexture("testPressed.png"));
    });

    Button button3("Missing texture test", TextureManager::getTexture("test2.png"), Vector2f(128, 0), [&button3]()->void{
        button3.getSprite().setTexture(TextureManager::getTexture("tested.png"));
    });

    UIElementManager::addElement(&button);
    UIElementManager::addElement(&button2);
    UIElementManager::addElement(&button3);

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
        UIElementManager::drawAllElements();
        window.display();
    }

    return 0;
}
