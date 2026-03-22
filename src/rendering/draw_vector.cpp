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

        // Compute interpolated X position if the bar is swapping.
        float xPos = i * rectWidth; // Default position.

        // For each swap in activeSwaps update swapping animation.
        for (const auto& swap : state.activeSwaps)
        {
            if (i == swap.indexA)
            {
                xPos = (1.0f - swap.progress) * swap.indexA * rectWidth
                     + swap.progress * swap.indexB * rectWidth;
            }
            else if (i == swap.indexB)
            {
                xPos = (1.0f - swap.progress) * swap.indexB * rectWidth
                     + swap.progress * swap.indexA * rectWidth;
            }
        }

        // Set up rectangle object and position.
        sf::RectangleShape rectangle(sf::Vector2f(rectWidth - 5.f, height));
        rectangle.setPosition(sf::Vector2f(xPos, windowHeight - height));

        // Set up color based on role.
        switch (state.roles[i])
        {
            case BarRole::Sorted:    rectangle.setFillColor(sf::Color::Green); break;
            case BarRole::Comparing: rectangle.setFillColor(sf::Color::Red);   break;
            case BarRole::Key:       rectangle.setFillColor(sf::Color::Blue);  break;
            default:                 rectangle.setFillColor(sf::Color::White); break;
        }

        window.draw(rectangle);
    }
}