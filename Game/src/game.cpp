#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include "game.h"
#include "canvas.h"
#include "config.h"
#include "entity.h"


Game::Game() noexcept(false) {
  this->window = SDL_CreateWindow(Window::Title, Window::Width, Window::Height, 0);

  if (this->window == nullptr) throw std::runtime_error(SDL_GetError());

  this->renderer = SDL_CreateRenderer(window, nullptr);

  if (this->renderer == nullptr) throw std::runtime_error(SDL_GetError());

  this->alien_spawn_rate = 4000;
  this->star_spawn_rate = 300;
  this->last_tick = SDL_GetTicks();
  this->last_alien_spawn = last_tick;
  this->last_star_spawn = last_tick;

  Player * player = new Player(this->renderer);

  this->player = player;
}

Game::~Game() {
  this->bullets.clear();
  this->stars.clear();
  this->aliens.clear();

  delete this->player;
  
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
}

void Game::loop() {
  Uint64 current_tick = SDL_GetTicks();

  if (current_tick - this->last_tick < Animation::FPS) return;

  std::erase_if(bullets, [&](auto &bullet){ return (bullet->destroyed); });
  std::erase_if(aliens, [&](auto &alien){ return (alien->destroyed); });
  std::erase_if(stars, [&](auto &star){ return (star->destroyed); });

  if (current_tick - this->last_star_spawn > this->star_spawn_rate) {
    this->spawn_star();
    this->last_star_spawn = current_tick;
  }

  if (current_tick - this->last_alien_spawn > this->alien_spawn_rate) {
    this->spawn_alien(Window::F_Width / 2, -10);
    this->last_alien_spawn = current_tick;
  }

  for (auto & event: this->events) {
    this->handle_event(event);
  }

  Canvas::clear(this->renderer);

  for (auto & star: this->stars) { star->animate(); }

  this->player->animate();

  for (auto & bullet: this->bullets) { bullet->animate(); }
  for (auto & alien: this->aliens) { alien->animate(); }

  for (auto & bullet: this-> bullets) {
    for (auto & alien: this->aliens) {
      auto a = alien->hitbox; 
      auto b = bullet->hitbox;

      if (SDL_HasRectIntersectionFloat(&a, &b)) {
        bullet->destroyed = true;
        alien->destroyed = true;
      }
    }
  }

  SDL_RenderPresent(this->renderer);
  this->last_tick = current_tick;
}

void Game::shoot(float player_x, float player_y, float player_height) {
  this->bullets.emplace_back(std::make_unique<Bullet>(
    this->renderer,
    player_x,
    player_y - (player_height / 2)
  ));
};

void Game::spawn_alien(float x, float y) {
  this->aliens.emplace_back(std::make_unique<Alien>(
    this->renderer,
    x,
    y
  ));  
};

void Game::spawn_star() {
  this->stars.emplace_back(std::make_unique<Star>(this->renderer));  
};

void Game::handle_event(SDL_Event *event) {
  switch (event->type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (event->button.button == SDL_BUTTON_LEFT) {
        break; 
      } else {
        break;
      }
      break;
    case SDL_EVENT_KEY_DOWN:
      if (event->key.key == SDLK_LEFT) {
        this->player->direction = -1;
        break;
      } else if (event->key.key == SDLK_RIGHT) {
        this->player->direction = 1;
        break;
      } else if (event->key.key == SDLK_SPACE) {
        this->shoot(this->player->x, this->player->y, this->player->h);
      }
      break;
    case SDL_EVENT_KEY_UP: 
      if (event->key.key == SDLK_LEFT || event->key.key == SDLK_RIGHT) {
        this->player->direction = 0;
      }
      break;
  };
};
