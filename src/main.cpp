// SFML & ImGui.
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
// Random & queue
#include <random>
#include <queue>
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
    float algoTimer = 0.0f;

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
    std::vector<int> logicalArr(size);

    VisualState state;
    state.roles.resize(arr.size());

    // Event queue for animations.
    std::queue<SortOp> opQueue;

    // Obtain a seed form a hardware source.
    std::random_device rd;
    // Initializae the random number generator.
    std::mt19937 gen(rd());

    initVector(arr, gen, state);
    logicalArr = arr;

    // Initial state of object based on first algorithm choice.
    SortAlgorithm* alg = createAlgorithm(logicalArr, 0);

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
                logicalArr = arr;
                sorted = false; // To cover when fully sorted
            }
            // Delete object & create a new one for selected algorithm. 
            delete alg;
            alg = createAlgorithm(logicalArr, selectedAlg);
            sorting = true;
            sortedEver = true;
            while (!opQueue.empty()) opQueue.pop(); // Clear the queue.
        }

        ImGui::SameLine();

        // Reset Button resets the vector displayed on screen.
        if (ImGui::Button("Reset"))
        {
            sorting = false;
            sorted = false;
            sortedEver = false;
            state.resetRoles(arr.size());
            initVector(arr, gen, state);
            logicalArr = arr;
            delete alg;
            alg = createAlgorithm(logicalArr, selectedAlg);
            while (!opQueue.empty()) opQueue.pop(); // Clear the queue.
        }

        ImGui::End();

        // Keep track of time elapsed for speed of sorting.
        float deltaTime = dt.asSeconds();
        stepDelay = 1.0f / speed;
        state.swapSpeed = speed / 10.0f;

        if (sorting && state.activeSwaps.empty())
        {
            timer += deltaTime;
            while (timer >= stepDelay)
            {
                SortOp op;
                bool stillSorting = alg->step(op);

                if (!stillSorting)
                {
                    sorting = false;
                    break;
                }

                opQueue.push(op);
                timer -= stepDelay;
            }
        }

        // Main sorting logic.
        // 1. Only process if there's no active animation & enough time has passed.
        if (state.activeSwaps.empty() && !opQueue.empty())
        {
            SortOp op = opQueue.front();
            opQueue.pop();

            state.resetNonSorted(arr.size());

            switch (op.type)
            {
                case OpType::Compare:
                    state.markComparingPair(op.a, op.b);
                    break;
                case OpType::Swap:
                    state.activeSwaps.push_back({op.a, op.b, 0.0f});
                    state.markComparingPair(op.a, op.b);
                    break;
                case OpType::Sorted:
                    state.markSorted(op.a);
                    break;
                default:
                    break;
            }
        }

        // BLOCK LOGIC while animating
        // 2. Update ongoing swap animations.
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

        // 3. Final completion check.
        if (!sorted && !sorting && sortedEver && opQueue.empty() && state.activeSwaps.empty())
        {
            sorted = true;
            // Make sure all bars marked sorted when finished.
            for (int k = 0; k < arr.size(); ++k)
            {
                state.markSorted(k);
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
