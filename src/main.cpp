// SFML & ImGui.
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
// Standard libraries.
#include <random>
#include <queue>
#include <iostream>
// Helpers.
#include "utils/init_vector.h"
#include "rendering/draw_vector.h"
#include "sorting_factory/create_algorithm.h"
#include "core/recorder.h"

int main()
{
    // Get current Monitor resolution & set window size to around 90% of that.
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowSize = desktopMode.size;
    unsigned int windowWidth = windowSize.x * 0.9f;
    unsigned int windowHeight = windowSize.y * 0.85f;

    // Create the window & set framerate.
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Sorting Visualizer");
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
    bool sortedEver = false;

    // Sorting Algorithms.
    static const char* algs[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"};
    static int selectedAlg = 0;

    // Size of vector.
    int size = 32;
    // Vector of integers.
    std::vector<int> arr(size);

    // Visual state object for the algorithm.
    VisualState state;
    state.roles.resize(arr.size());

    // Event queue for animations.
    std::queue<SortEvent> eventQueue;

    // Obtain a seed form a hardware source.
    std::random_device rd;
    // Initializae the random number generator.
    std::mt19937 gen(rd());

    initVector(arr, gen, state);

    // Initial state of object based on first algorithm choice.
    SortAlgorithm* alg = createAlgorithm(0);

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

        // Sort Button to initiate teh selected algorithm.
        if (ImGui::Button("Sort"))
        {
            // If button is pressed while algorithm is running reset the vector.
            if ((sorting && !sorted) || sorted)
            {
                state.resetRoles(arr.size());
                initVector(arr, gen, state);
            }

            // Clear the previous queue & any active animations.
            while (!eventQueue.empty()) eventQueue.pop(); 
            state.activeSwaps.clear();

            // Create working copy for algorithm.
            std::vector<int> workingArr = arr;

            // Recreate algorithm. 
            delete alg;
            alg = createAlgorithm(selectedAlg);

            // Set Callback before running algorithm.
            alg->onEvent = [&](const SortEvent& event)
            {
                // Enqueue event for animation
                eventQueue.push({event.type, event.a, event.b, event.value});
            };

            // Run algorithm.
            alg->run(workingArr);

            // Reset flags.
            sorting = true;
            sortedEver = true;
            sorted = false;
            timer = 0.0f; // Reset timer from previous sorts.
        }

        ImGui::SameLine(); // Buttons on same line on screen.

        // Reset Button resets the vector displayed on screen.
        if (ImGui::Button("Reset"))
        {
            // Clear the previous queue.
            while (!eventQueue.empty()) eventQueue.pop(); 

            // Clear any active animations.
            state.activeSwaps.clear();
        
            // Re-initialize vector.
            state.resetRoles(arr.size());
            initVector(arr, gen, state);

            // Recreate algorithm.
            delete alg;
            alg = createAlgorithm(selectedAlg);

            // Reset flags.
            sorting = false;
            sorted = false;
            sortedEver = false;
            timer = 0.0f; // Reset timer from previous sorts.
        }

        ImGui::End();

        // Animation timing variables.
        float deltaTime = dt.asSeconds();
        stepDelay = 1.0f / speed;
        state.swapSpeed = speed / 10.0f;

        // Main sorting logic.
        if (sorting)
        {
            timer += deltaTime;

            while (timer >= stepDelay && !eventQueue.empty())
            {
                if (state.activeSwaps.empty())
                {
                    // Operation object to be visualized.
                    SortEvent event = eventQueue.front();
                    eventQueue.pop();

                    // Reset all bars visually that are not marked as sorted.
                    state.resetNonSorted(arr.size());

                    switch (event.type)
                    {
                        case OpType::Compare:
                            state.markComparing(event.a);
                            break;

                        case OpType::ComparePair:
                            state.markComparingPair(event.a, event.b);
                            break;

                        case OpType::Swap:
                            state.activeSwaps.push_back({event.a, event.b, 0.0f});
                            state.markComparingPair(event.a, event.b);
                            break;

                        case OpType::Sorted:
                            state.markSorted(event.a);
                            break;
                        
                        case OpType::Overwrite:
                            arr[event.a] = event.value;
                            break;

                        case OpType::Key:
                            state.markKey(event.a, arr[event.a]);

                        default:
                            break;
                    }
                }

                // Reapply key to vector
                if (state.hasKey)
                {
                    state.markKey(state.keyIndex, arr[state.keyIndex]);
                }

                timer -= stepDelay;
            }

            // Finish condition.
            if (eventQueue.empty() && state.activeSwaps.empty())
            {
                sorting = false;
                sorted = true;

                // Make sure all bars are marked sorted.
                for (int k = 0; k < arr.size(); ++k)
                {
                    state.markSorted(k);
                }
            }
        }

        // Update ongoing swap animations.
        for (auto it = state.activeSwaps.begin(); it != state.activeSwaps.end(); )
        {
            it->progress += deltaTime * state.swapSpeed;

            if (it->progress >= 1.0f)
            {
                std::swap(arr[it->indexA], arr[it->indexB]);
                it = state.activeSwaps.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Clear the SFML Window.
        window.clear();

        // Reset the OpenGL state
        window.resetGLStates();

        drawVector(arr, state, window);

        // Render ImGui & SFML Content.
        ImGui::SFML::Render(window);
        window.display();
    }

    // Window closed, delete algorithm & shutdown.
    delete alg;
    ImGui::SFML::Shutdown();
}