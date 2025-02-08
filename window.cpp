#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_Log("SDL_Init failed! SDL Error: %s", SDL_GetError());

      return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
      "SDL3 Rectangle Fill",
      640,
      480,
      0
    );

    if (window == nullptr) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect fillRect = { 100.0f, 100.0f, 200.0f, 150.0f };
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

