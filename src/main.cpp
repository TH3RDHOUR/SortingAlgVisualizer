#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL failed to initialize\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Sorting Visualizer",
        800,
        600,
        0
    );

    if (!window)
    {
        std::cout << "Window failed to create\n";
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        SDL_Delay(16); // ~60fps
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}