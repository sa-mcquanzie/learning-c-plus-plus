#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include "entity.hpp"


class Game {
  public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player *player;
    StatusBar *status_bar;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Alien>> aliens;
    std::vector<std::unique_ptr<Star>> stars;
    std::vector<SDL_Event *> events;
    Uint64 star_spawn_rate;
    Uint64 alien_spawn_rate;
    Uint64 last_star_spawn;
    Uint64 last_alien_spawn;
    Uint64 last_tick;
    int window_pixel_w;
    int window_pixel_h;
    int score;
    int lives;

    Game();

    ~Game(void);

    void loop();
    void add_entity(EntityType entity_type, float x, float y, bool visible);
    void spawn_player();
    void spawn_star();
    void spawn_alien(AlienVariant variant, float x, float y);
    void shoot(float player_x, float player_y, float player_h, float player_w);
    void handle_event(SDL_Event *event);
};
