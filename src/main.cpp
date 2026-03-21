// SFML & ImGui.
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
// Random
#include <random>
// Helpers.
#include "utils/init_vector.h"
#include "rendering/draw_vector.h"
#include "sorting_factory/create_algorithm.h"

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
    if (!ImGui::SFML::Init(window))
    {
        std::cout << "Failed to initialize ImGui Window." << std::endl;
        return -1;
    }

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
    static const char* algs[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"};
    static int selectedAlg = 0;

    // Size of vector.
    int size = 32;

    // Vector of integers.
    std::vector<int> arr(size);

    VisualState state;
    state.roles.resize(arr.size());

    // Obtain a seed form a hardware source.
    std::random_device rd;
    // Initializae the random number generator.
    std::mt19937 gen(rd());

    initVector(arr, gen, state);

    // Initial state of object based on first algorithm choice.
    SortAlgorithm* alg = createAlgorithm(arr, 0);

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

        // Sort Button calls the sorting.
        if (ImGui::Button("Sort"))
        {
            // If button is pressed while algorithm is running reset the vector.
            if ((sorting && !sorted) || sorted)
            {
                state.resetRoles(arr.size());
                initVector(arr, gen, state);
                sorted = false; // To cover when fully sorted
            }
            // Delete object & create a new one for selected algorithm. 
            delete alg;
            alg = createAlgorithm(arr, selectedAlg);
            sorting = true;
        }

        ImGui::SameLine();

        // Reset Button resets the vector displayed on screen.
        if (ImGui::Button("Reset"))
        {
            sorting = false;
            sorted = false;
            state.resetRoles(arr.size());
            initVector(arr, gen, state);
            delete alg;
            alg = createAlgorithm(arr, selectedAlg);
        }

        ImGui::End();

        // Keep track of time elapsed for speed of sorting.
        float deltaTime = dt.asSeconds();
        stepDelay = 1.0f / speed;

        // Keep sorting while there is still numbers to sort.
        if (sorting)
        {
            timer += deltaTime;

            // Sorting Loop.
            while (timer >= stepDelay)
            {
                SortOp op;

                 // Reset only non-sorted bars
                state.resetNonSorted(arr.size());

                sorting = alg->step(op);

                // 1. Apply operation.
                if (op.type == OpType::Swap)
                {
                    std::swap(arr[op.a], arr[op.b]);
                }

                // 2. Update visuals.
                if (op.type == OpType::Compare)
                {
                    state.markComparingPair(op.a, op.b);
                }
                else if (op.type == OpType::Swap)
                {
                    state.markComparingPair(op.a, op.b);
                }
                else if (op.type == OpType::Sorted)
                {
                    state.markSorted(op.a);
                }

                // Check if still sorting.
                if (!sorting)
                {
                    sorted = true;

                    // Make sure all bars are marked sorted when done.
                    for (int k = 0; k < arr.size(); ++k)
                    {
                        state.markSorted(k);
                    }
                }

                // Decrement timer.
                timer -= stepDelay;
            }
        }

        // Clear the SFML Window.
        window.clear();

        // Reset the OpenGL state
        window.resetGLStates();

        drawVector(arr, state, window);

        // Render ImGui Content.
        ImGui::SFML::Render(window);

        // Render SFML content.
        window.display();
    }

    ImGui::SFML::Shutdown();
}
