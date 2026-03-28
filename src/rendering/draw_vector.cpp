#include "rendering/draw_vector.h"

void drawVector(std::vector<int>& arr, const VisualState& state, sf::RenderWindow& window)
{
    // Get window height & width for sizing/re-sizing.
    float windowHeight = window.getSize().y;
    float windowWidth = window.getSize().x;
    float rectWidth = windowWidth / arr.size();

    // Dervied state for floating key index.
    int gapIndex = state.hasFloatingKey ? state.keyTargetIndex : -1;

    for (int i = 0; i < arr.size(); ++i)
    {
        // Compute interpolated X position if the bar is swapping and/or moving.
        float xPos = i * rectWidth; // Default position.
        int height = arr[i];

        bool isAnimating = false;
        bool isTargetofAnimation = false;

        // Loop through all animations & show animation on screen.
        for (const auto& anim : state.activeAnimations)
        {
            if (i == anim.fromA)
            {
                isTargetofAnimation = true;
                xPos = (1.0f - anim.progress) * anim.fromA * rectWidth
                    + anim.progress * anim.toA * rectWidth;
                height = anim.valueA;
                isAnimating = true;
            }

            if (anim.fromB != -1 && i == anim.fromB)
            {
                xPos = (1.0f - anim.progress) * anim.fromB * rectWidth
                    + anim.progress * anim.toB * rectWidth;
                height = anim.valueB;
                isAnimating = true;
            }
        }

        // Do not show the gap index below the floating key value.
        if (state.hasFloatingKey && (i == gapIndex || isTargetofAnimation))
        {
            continue;
        }

        // Draw rectangle (animated or static)
        sf::RectangleShape rectangle(sf::Vector2f(rectWidth - 5.f, height));
        rectangle.setPosition(sf::Vector2f(xPos, windowHeight - height));

        // Set up color based on role.
        switch (state.roles[i])
        {
            case BarRole::Sorted:    rectangle.setFillColor(sf::Color::Green); break;
            case BarRole::Comparing: rectangle.setFillColor(sf::Color::Red);   break;
            case BarRole::Key:       rectangle.setFillColor(sf::Color::Blue);  break;
            case BarRole::LeftHalf:  rectangle.setFillColor(sf::Color(100, 150, 255)); break; // Soft Blue.
            case BarRole::RightHalf: rectangle.setFillColor(sf::Color(255, 150, 100)); break; // Soft Orange.
            default:                 rectangle.setFillColor(sf::Color::White); break;
        }

        window.draw(rectangle);
    }

    // Determine the tallest bar height.
    int maxHeight = 0;
    for (int h : arr) if (h > maxHeight) maxHeight = h;

    // Animate the key bar separately
    if (state.hasFloatingKey)
    {
        float x = state.keyTargetIndex * rectWidth;

        // Animate x-position if we added a key animation
        for (const auto& anim : state.activeAnimations)
        {
            if (anim.valueA == state.keyValue) // Special ID for floating key animation
            {
                x = (1.0f - anim.progress) * anim.fromA * rectWidth
                + anim.progress * anim.toA * rectWidth;
            }
        }

        float y = windowHeight - maxHeight - 50.0f; // floating above all bars

        sf::RectangleShape keyRect(sf::Vector2f(rectWidth - 5.f, state.keyValue));
        keyRect.setPosition(sf::Vector2f(x, y));
        keyRect.setFillColor(sf::Color::Blue);

        window.draw(keyRect);
    }
}