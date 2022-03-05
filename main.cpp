#include <iostream>
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 500), "Media Compression by iCompression ");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}
