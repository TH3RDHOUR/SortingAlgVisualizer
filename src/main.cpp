#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the window.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sorting Visualizer");

    while (window.isOpen())
    {
        // Check Window events triggered since last iteration of the loop.
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Create Rectangle .
        sf::RectangleShape rectangle({50.0f, 120.0f});

        window.draw(rectangle);

        // Take what is drawn and show on the Window.
        window.display();
    }
}