#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <random>
#include <vector>

#include "sorting/bubble_sort.h"
#include "utils/init_vector.h"
#include "rendering/draw_vector.h"
#include "sorting/SortAlgorithm.h"

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

    // Sorting Algorithms.
    static const char* algs[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort"};
    static int selectedAlg = 0;

    // Size of vector.
    int size = 32;

    // Vector of integers.
    std::vector<int> arr(size);

    // Obtain a seed form a hardware source.
    std::random_device rd;
    // Initializae the random number generator.
    std::mt19937 gen(rd());

    initVector(arr, gen);

    BubbleSort bubs(arr);

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
                    initVector(arr, gen);
                    bubs.reset();
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

        // Set ImGui Window size.
        ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Always);

        // Build ImGui UI (including the slider)
        ImGui::Begin("Sorting Speed Controller"); // Start a new ImGui window

        // Add the slider widget
        ImGui::SliderFloat("Sort Speed (ops/sec)", &speed, 1.0f, 500.0f);

        ImGui::Text("Current slider value: %.3f", speed);

        // Dropdown Algorithm Selector
        ImGui::Combo("Sorting Algorithm", &selectedAlg, algs, IM_ARRAYSIZE(algs));
// TODO: need to implement using the Combo for which algorithm to run instead of number press.
// Probably will need a start button as well.
        ImGui::End();

        // Keep track of time elapsed for speed of sorting.
        float deltaTime = dt.asSeconds();
        stepDelay = 1.0f / speed;

        // Keep sorting while there is still numbers to sort.
        if (sorting)
        {
            timer += deltaTime;

            while (timer >= stepDelay)
            {
                // sorting = bubbleSort(arr, i, j);
                sorting = bubs.step();
                if (!sorting)
                {
                    sorted = true;
                }
                timer -= stepDelay;
            }
        }

        // Clear the SFML Window.
        window.clear();

        // Reset the OpenGL state
        window.resetGLStates();

        // Draw all rectangles & objects on the window.
        drawVector(arr, window, bubs.getCurrentIndex1(), bubs.getCurrentIndex2(), 
        bubs.getSortedStart(), sorting, sorted);

        // Render ImGui Content.
        ImGui::SFML::Render(window);

        // Render SFML content.
        window.display();
    }

    ImGui::SFML::Shutdown();
}
