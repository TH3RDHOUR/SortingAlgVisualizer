// SFML & ImGui.
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
// Standard libraries.
#include <random>
#include <queue>
#include <iostream>
// Local files.
#include "utils/init_vector.h"
#include "rendering/draw_vector.h"
#include "sorting_factory/create_algorithm.h"

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
    std::unique_ptr<SortAlgorithm> alg = algorithms[0].create();

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

        // Set ImGui Window position & size.
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(320, 0), ImGuiCond_Always);

        // Build ImGui UI (including the slider)
        ImGui::Begin("Sorting Controls"); // Start a new ImGui window

        // Add the slider widget for sort speed.
        ImGui::SliderFloat("Speed", &speed, 1.0f, 500.0f);

        ImGui::Spacing();

        ImGui::Text("Algorithm");
        // Dropdown Algorithm Selector using lambda to fill in values.
        ImGui::Combo("##Algorithm", &selectedAlg,
        [](void* data, int idx, const char** out_text)
        {
            const AlgorithmInfo* algs = static_cast<AlgorithmInfo*>(data);
            *out_text = algs[idx].name;
            return true;
        },
        (void*)algorithms,
        getNumAlgs()
        );

        ImGui::Spacing();

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
            state.activeAnimations.clear();

            // Create working copy for algorithm.
            std::vector<int> workingArr = arr;

            // Recreate algorithm. 
            //alg = createAlgorithm(selectedAlg);
            alg = algorithms[selectedAlg].create();

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
            state.activeAnimations.clear();
        
            // Re-initialize vector.
            state.resetRoles(arr.size());
            initVector(arr, gen, state);

            // Recreate algorithm.
            //alg = createAlgorithm(selectedAlg);
            alg = algorithms[selectedAlg].create();

            // Reset flags.
            sorting = false;
            sorted = false;
            sortedEver = false;
            timer = 0.0f; // Reset timer from previous sorts.
        }

        // Get this windo's size & position for second window.
        ImVec2 firstPos = ImGui::GetWindowPos();
        ImVec2 firstSize = ImGui::GetWindowSize();

        ImGui::End();

        // For sizing the algorithm info window.
        float leftWidth = 320.f;
        float spacing = 10.0f;
        float rightX = 10.0f + leftWidth + spacing;
        float rightWidth = window.getSize().x - rightX - 100.0f;

        // Set window position based on first ImGui window.
        ImGui::SetNextWindowPos(ImVec2(rightX, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(rightWidth, 0), ImGuiCond_Always);

        // Algorithm Information window.
        ImGui::Begin("Big O Notation");

        // Get all the information on the selected algorithm in combobox.
        const AlgorithmInfo& info = algorithms[selectedAlg];

        ImGui::Text("%s", info.name);
        ImGui::Separator();

        float wrapWidth = ImGui::GetContentRegionAvail().x;

        // Description block.
        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrapWidth);
        ImGui::TextWrapped("%s", info.description);
        ImGui::PopTextWrapPos();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::BeginTable("Complexity", 2, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Best");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", info.bestCase);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Average");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", info.avgCase);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Worst");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", info.worstCase);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Space");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", info.spaceComp);

            ImGui::EndTable();
        }

        ImGui::Spacing();

        // Properties.
        ImGui::Text("Stable:   %s", info.stable ? "Yes" : "No");
        ImGui::Text("In-Place: %s", info.inPlace ? "Yes" : "No");

        ImGui::End();

        // Animation timing variables.
        float deltaTime = dt.asSeconds(); // Time since last frame.
        stepDelay = 1.0f / speed;
        state.swapSpeed = speed / 10.0f;

        // Main sorting logic.
        if (sorting)
        {
            // Time accumulation for proper animations.
            timer += deltaTime;

            // Loop over every event using stepDelay with timer to control the time elapsed.
            while (timer >= stepDelay && !eventQueue.empty())
            {
                // If not active animations to prevent overlapping animations.
                if (state.activeAnimations.empty())
                {
                    // Reset all bars visually that are either comparing or a key role.
                    state.resetNonSorted(arr.size());

                    // Operation object to be visualized.
                    SortEvent event = eventQueue.front();
                    eventQueue.pop();

                    switch (event.type)
                    {
                        case OpType::Compare:
                            state.markComparing(event.a);
                            break;

                        case OpType::ComparePair:
                            state.markComparingPair(event.a, event.b);
                            break;

                        case OpType::Swap:
                            state.activeAnimations.push_back({
                                event.a, event.b,
                                event.b, event.a,
                                arr[event.a], arr[event.b],
                                0.0f
                            });
                            break;

                        case OpType::Shift:
                            state.activeAnimations.push_back({
                                event.a, event.b,
                                -1, -1,
                                event.value, 0,
                                0.0f
                            });

                            // Key moves at the same time.
                            state.activeAnimations.push_back({
                                state.keyCurrentIndex, event.a,
                                -1, -1,
                                state.keyValue, 0,
                                0.0f
                            });

                            state.keyCurrentIndex = event.a;
                            state.keyTargetIndex = event.a;
                            state.movingFromIndex = event.a;
                            break;

                        case OpType::Sorted:
                            state.markSorted(event.a);
                            break;
                        
                        case OpType::Overwrite:
                            arr[event.a] = event.value;
                            break;

                        case OpType::Key:
                            state.markKey(event.a, arr[event.a]);
                            break;

                        case OpType::KeyPickup:
                            state.hasFloatingKey = true;
                            state.keyValue = event.value;
                            state.keyCurrentIndex = event.a;
                            state.keyTargetIndex = event.a;
                            break;

                        case OpType::KeyPlace:
                            state.hasFloatingKey = false;
                            arr[event.a] = event.value;
                            break;
                        
                        case OpType::MarkLeftRange:
                            state.markLeftHalf(event.a, event.b);
                            break;

                        case OpType::MarkRightRange:
                            state.markRightHalf(event.a, event.b);
                            break;

                        default:
                            break;
                    }
                }

                // Reapply key to vector
                if (state.hasKey)
                {
                    state.markKey(state.keyIndex, arr[state.keyIndex]);
                }

                // Decrement timer, (i.e time has progressed)
                timer -= stepDelay;
            }

            // Finish condition.
            if (eventQueue.empty() && state.activeAnimations.empty())
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

        // Update all ongoing animations using the iterator it (not an index).
        for (auto it = state.activeAnimations.begin(); it != state.activeAnimations.end(); )
        {
            // Progress from 0.0 to 1.0 at a speed.
            it->progress += deltaTime * state.swapSpeed;

            // If animation is complete
            if (it->progress >= 1.0f)
            {
                // Apply final state
                // A always moves
                arr[it->toA] = it->valueA;

                // If it's a swap, apply B too.
                if (it->fromB != -1)
                {
                    arr[it->toB] = it->valueB;
                }

                // Cleanup animation state.
                state.movingFromIndex = -1;

                // Remove finished animation (don't iterate it).
                it = state.activeAnimations.erase(it);
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
    ImGui::SFML::Shutdown();
}