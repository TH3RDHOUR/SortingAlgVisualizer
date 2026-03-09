#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, int currentIndex1, 
                int currentIndex2, int sortedStart, bool sorting, bool sorted);
bool bubbleSortStep(std::vector<int>& arr, int& i, int& j);

int main()
{
    // Create the window.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sorting Visualizer");
    // Slow down Framerate to see the swaps take place.
    window.setFramerateLimit(30);

    // Sorting variables.
    bool sorting = false;
    bool sorted = false;
    int i = 0;
    int j = 0;

    // Size of vector.
    int size = 32;

    // Vector of integers.
    std::vector<int> arr(size);

    // Obtain a seed form a hardware source.
    std::random_device rd;
    // Initializae the random number generator.
    std::mt19937 gen(rd());
    // Define the number distribution.
    std::uniform_int_distribution<> distrib(1, 500);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = distrib(gen);
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

            if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::Num0)
                {
                    sorting = true;
                    std::cout << "Pressed Zero!" << std::endl;
                }
            }
        }

        if (sorting)
        {
            sorting = bubbleSortStep(arr, i, j);
            if (!sorting)
                sorted = true;
        }

        drawVector(arr, window, j, j + 1, arr.size() - i, sorting, sorted);
    }
}

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, 
                int currentIndex1, int currentIndex2, int sortedStart, 
                bool sorting, bool sorted)
{
    window.clear();
    for (int i = 0; i < arr.size(); ++i)
    {
        // Get window height & width for sizing/re-sizing.
        float windowHeight = window.getSize().y;
        float windowWidth = window.getSize().x;
        float rectWidth = windowWidth / arr.size();

        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i]));
        rectangle.setSize(sf::Vector2f(rectWidth - 5.f, arr[i]));

        // Space out rectangles & set height based on bottom of the screen size.
        rectangle.setPosition(sf::Vector2f(i * rectWidth, windowHeight - arr[i]));

        // If sorting & comparing rects turn red, already sorted turn green, otherwise white.
        if (!sorting && sorted)
        {
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
    window.display();
    sf::sleep(sf::milliseconds(10));
}

bool bubbleSortStep(std::vector<int>& arr, int& i, int& j)
{
    // Sorting is finished.
    if (i >= arr.size() - 1)
    {
        return false;
    }
    // j has reached the end, restart & increment i.
    if (j == arr.size() - i - 1)
    {
        j = 0;
        i++;
        return i < arr.size() - 1;
    }
    else if (arr[j] > arr[j + 1])
    {
        std::swap(arr[j], arr[j + 1]);
    }
    j++;
    return i < arr.size() - 1;
}
