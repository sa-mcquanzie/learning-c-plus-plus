#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_events.h>
#include <exception>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "game.hpp"


SDL_AppResult SDL_AppInit(void **game, int, char **) {
  try {
    *game = new Game();

    return SDL_APP_CONTINUE;
  } catch (const std::exception& e) {
    SDL_Log("%s", e.what());
    
    return SDL_APP_FAILURE;
  }
}

SDL_AppResult SDL_AppIterate(void *g) {
  Game& game = *static_cast<Game*>(g);

  game.loop();
  
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *g, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

  Game& game = *static_cast<Game*>(g);

  game.events.push_back(event);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *g, SDL_AppResult) {
  Game* game = static_cast<Game*>(g);

  delete game;
}
