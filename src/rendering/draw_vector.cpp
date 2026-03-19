#include "rendering/draw_vector.h"

void drawVector(std::vector<int>& arr, std::vector<BarRole>& roles, sf::RenderWindow& window)
{
    // Get window height & width for sizing/re-sizing.
    float windowHeight = window.getSize().y;
    float windowWidth = window.getSize().x;
    float rectWidth = windowWidth / arr.size();

    for (int i = 0; i < arr.size(); ++i)
    {
        // Set up rectangle object.
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i]));
        rectangle.setSize(sf::Vector2f(rectWidth - 5.f, arr[i]));

        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * rectWidth, windowHeight - arr[i]));

        // If sorted(green), comparing(red), default(white).
        if (roles[i] == BarRole::Sorted)
        {
            rectangle.setFillColor(sf::Color::Green);
        }
        else if (roles[i] == BarRole::Comparing)
        {
            rectangle.setFillColor(sf::Color::Red);
        }
        else if (roles[i] == BarRole::Default)
        {
            rectangle.setFillColor(sf::Color::White);
        }
        else if (roles[i] == BarRole::Key)
        {
            rectangle.setFillColor(sf::Color::Blue);
        }

        window.draw(rectangle);
    }
}