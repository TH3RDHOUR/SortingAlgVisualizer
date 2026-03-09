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

            // Handle the window being resized.
            if (auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, 
                    {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                window.setView(sf::View(visibleArea));
            }
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
        // Get window height for rectangles to be on bottom.
        float windowHeight = window.getSize().y;
        float windowWidth = window.getSize().x;
        float rectWidth = windowWidth / arr.size();

        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i]));
        rectangle.setSize(sf::Vector2f(rectWidth - 5.f, arr[i]));

        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * rectWidth, windowHeight - arr[i]));
        rectangle.setFillColor(sf::Color::White);

        window.draw(rectangle);
    }
    window.display();
}

