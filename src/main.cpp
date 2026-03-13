#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <random>
#include <vector>

void initVector(std::vector<int>& arr, std::mt19937& gen);
void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, int currentIndex1, 
                int currentIndex2, int sortedStart, bool sorting, bool sorted);
bool bubbleSort(std::vector<int>& arr, int& i, int& j);

int main()
{
    // Get current Monitor resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Reduce the window size to around 90%.
    sf::Vector2u windowSize = desktopMode.size;
    unsigned int windowWidth = windowSize.x * 0.9f;
    unsigned int windowHeight = windowSize.y * 0.85f;

    // Create the window.
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Sorting Visualizer");
    // Slow down Framerate to see the swaps take place.
    window.setFramerateLimit(120);

    // Center the screen.
    window.setPosition(sf::Vector2i(
        (windowSize.x - windowWidth) / 2,
        (windowSize.y - windowHeight) / 2
  ));

    // Initialize IMGUI-SFML.
    ImGui::SFML::Init(window);

    // Make ImGui text larger.
    ImGui::GetIO().FontGlobalScale = 1.6f;
    ImGui::GetStyle().ScaleAllSizes(1.4f);

    // GUI variables.
    float stepDelay = 0.05f;
    float speed = 20.0f;
    float timer = 0.0f;

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

    initVector(arr, gen);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        // Check Window events triggered since last iteration of the loop.
        while (auto event = window.pollEvent())
        {
            // Pass events to ImGui-SFML event processor
            ImGui::SFML::ProcessEvent(window, event.value());

            // If the window is closed.
            if (event->is<sf::Event::Closed>())
                window.close();

            // Handle the window being resized.
            if (auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, 
                    {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                window.setView(sf::View(visibleArea));
            }

            // If a key is pressed.
            if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                // Number zero pressed, reset the array & window.
                if (keyEvent->code == sf::Keyboard::Key::Num0)
                {
                    sorting = false;
                    sorted = false;
                    i = 0;
                    j = 0;
                    initVector(arr, gen);
                }

                // Number 1 pressed, Bubble Sort.
                else if (keyEvent->code == sf::Keyboard::Key::Num1)
                {
                    sorting = true;
                }
            }
        }
        // Restart the clock once per frame.
        sf::Time dt = deltaClock.restart();

        // Update ImGui.
        ImGui::SFML::Update(window, dt);

        // Build ImGui UI (including the slider)
        ImGui::Begin("Sorting Speed Controller"); // Start a new ImGui window

        // Add the slider widget
        ImGui::SliderFloat("Sort Speed (ops/sec)", &speed, 1.0f, 500.0f);

        ImGui::Text("Current slider value: %.3f", speed);

        ImGui::End();

        float deltaTime = dt.asSeconds();
        stepDelay = 1.0f / speed;

        // Keep sorting while there is still numbers to sort.
        if (sorting)
        {
            timer += deltaTime;

            while (timer >= stepDelay)
            {
                sorting = bubbleSort(arr, i, j);
                if (!sorting)
                {
                    sorted = true;
                }
                timer -= stepDelay;
            }
        }

        drawVector(arr, window, j, j + 1, arr.size() - i, sorting, sorted);

        // Render ImGui Content.
        ImGui::SFML::Render(window);

        // Render SFML content.
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void initVector(std::vector<int>& arr, std::mt19937& gen)
{
    // Define the number distribution.
    std::uniform_int_distribution<> distrib(1, 500);

    // Fill the array with random numbers.
    for (int& num : arr)
    {
        num = distrib(gen);
    }
}

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, 
                int currentIndex1, int currentIndex2, int sortedStart, 
                bool sorting, bool sorted)
{
    // Get window height & width for sizing/re-sizing.
    float windowHeight = window.getSize().y;
    float windowWidth = window.getSize().x;
    float rectWidth = windowWidth / arr.size();

    window.clear();

    for (int i = 0; i < arr.size(); ++i)
    {
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
}

bool bubbleSort(std::vector<int>& arr, int& i, int& j)
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
    // if we need to swap the elements.
    else if (arr[j] > arr[j + 1])
    {
        std::swap(arr[j], arr[j + 1]);
    }
    // Increment j & return bool of if i has reached the end of vector.
    j++;
    return i < arr.size() - 1;
}
