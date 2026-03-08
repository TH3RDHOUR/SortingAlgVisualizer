#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

void bubbleSort(std::vector<sf::RectangleShape>& rectangles)
{
    return;
}

int main()
{
    // Create the window.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sorting Visualizer");

    // Vector of rectange objects.
    std::vector<sf::RectangleShape> rectangles(32);

    for (int i = 0; i < 32; ++i)
    {
        rectangles[i].setSize(sf::Vector2f(20, (float)((rand() % 50) + 1)));

        // Get window height for rectangles to be on bottom.
        float windowHeight = window.getSize().y;
        // Space out rectangles & set height based on bottom of the screen size.
        rectangles[i].setPosition(sf::Vector2f(i * 25, windowHeight - rectangles[i].getSize().y));
        rectangles[i].setFillColor(sf::Color::White);
    }

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

        for (const auto& rectangle : rectangles)
        {
            window.draw(rectangle);
        }

        // Take what is drawn and show on the Window.
        window.display();

        bubbleSort(rectangles);
    }
}