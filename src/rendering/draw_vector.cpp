#include "rendering/draw_vector.h"

// Draw the vector, this is where the color changes take place.
void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, 
                int currentIndex1, int currentIndex2, int sortedStart, 
                bool sorting, bool sorted)
{
    // Get window height & width for sizing/re-sizing.
    float windowHeight = window.getSize().y;
    float windowWidth = window.getSize().x;
    float rectWidth = windowWidth / arr.size();

    for (int i = 0; i < arr.size(); ++i)
    {
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i]));
        rectangle.setSize(sf::Vector2f(rectWidth - 5.f, arr[i]));

        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * rectWidth, windowHeight - arr[i]));

        // If sorting & comparing rects turn red, already sorted turn green, otherwise white.
        if (!sorting && sorted)
        {
            // Make sure the final rectangles are changed to green after finished.
            rectangle.setFillColor(sf::Color::Green); // All done.
        }
        else if (sorting && (i == currentIndex1 || i == currentIndex2))
        {
            rectangle.setFillColor(sf::Color::Red); // Currently comparing.
        }
        else if (i >= sortedStart)
        {
            rectangle.setFillColor(sf::Color::Green); // Done sorting.
        }
        else
        {
            rectangle.setFillColor(sf::Color::White); // Unsorted.
        }

        window.draw(rectangle);
    }
}