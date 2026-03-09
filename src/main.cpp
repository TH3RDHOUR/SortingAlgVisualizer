#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window);

int main()
{
    // Create the window.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sorting Visualizer");

    int size = 32;

    // Vector of integers.
    std::vector<int> arr(size);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = (rand() % 500) + 1;
    }

    while (window.isOpen())
    {
        // Check Window events triggered since last iteration of the loop.
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        drawVector(arr, window);

        //bubbleSort(rectangles, size, window);
    }
}

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window)
{
    window.clear();
    for (int i = 0; i < arr.size(); ++i)
    {
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i]));
        rectangle.setSize(sf::Vector2f(20, arr[i]));

        // Get window height for rectangles to be on bottom.
        float windowHeight = window.getSize().y;
        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * 25, windowHeight - rectangle.getSize().y));
        rectangle.setFillColor(sf::Color::White);
        window.draw(rectangle);
    }
    window.display();
}

