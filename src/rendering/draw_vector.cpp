#include "rendering/draw_vector.h"

void drawVector(std::vector<int>& arr, const VisualState& state, sf::RenderWindow& window)
{
    // Get window height & width for sizing/re-sizing.
    float windowHeight = window.getSize().y;
    float windowWidth = window.getSize().x;
    float rectWidth = windowWidth / arr.size();

    for (int i = 0; i < arr.size(); ++i)
    {
        int height = arr[i];

        // Override key's height for better visualization.
        if (i == state.keyIndex && state.hasKey)
        {
            height = state.keyValue;
        }

        // Set up rectangle object.
        sf::RectangleShape rectangle(sf::Vector2f(20, height));
        rectangle.setSize(sf::Vector2f(rectWidth - 5.f, height));

        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * rectWidth, windowHeight - height));

        // If sorted(green), comparing(red), default(white), key(blue).
        if (state.roles[i] == BarRole::Sorted)
        {
            rectangle.setFillColor(sf::Color::Green);
        }
        else if (state.roles[i] == BarRole::Comparing)
        {
            rectangle.setFillColor(sf::Color::Red);
        }
        else if (state.roles[i] == BarRole::Default)
        {
            rectangle.setFillColor(sf::Color::White);
        }
        else if (state.roles[i] == BarRole::Key)
        {
            rectangle.setFillColor(sf::Color::Blue);
        }

        window.draw(rectangle);
    }
}