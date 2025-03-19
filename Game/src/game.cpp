#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include "game.hpp"
#include "canvas.hpp"
#include "config.hpp"
#include "entity.hpp"

Game::Game() noexcept(false) {
  this->window = SDL_CreateWindow(Window::Title, Window::Width, Window::Height, 0);

  if (this->window == nullptr) throw std::runtime_error(SDL_GetError());

  this->renderer = SDL_CreateRenderer(window, nullptr);

  if (this->renderer == nullptr) throw std::runtime_error(SDL_GetError());

  SDL_GetWindowSizeInPixels(this->window, &this->window_pixel_w, &this->window_pixel_h);

  this->alien_spawn_rate = 4000;
  this->star_spawn_rate = 300;
  this->last_tick = SDL_GetTicks();
  this->last_alien_spawn = last_tick;
  this->last_star_spawn = last_tick;
  this->score = 0;
  this->lives = 3;

  Player * player = new Player(this->renderer);
  StatusBar * status_bar = new StatusBar(this->renderer);

  this->player = player;
  this->status_bar = status_bar;

  float row_1 = 200;
  float row_2 = 150;
  float row_3 = 100;
  float row_4 = 50;
  float row_5 = 0;

  float octopus_x = 98;

  for (int i = 0; i < 11; i++) {
    this->spawn_alien(AlienVariant::Octopus, octopus_x, row_1);
    octopus_x += (15 * 5);
  }

  octopus_x = 98;

  for (int i = 0; i < 11; i++) {
    this->spawn_alien(AlienVariant::Octopus, octopus_x, row_2);
    octopus_x += (15 * 5);
  }

  float crab_x = 100;

  for (int i = 0; i < 11; i++) {
    this->spawn_alien(AlienVariant::Crab, crab_x, row_3);
    crab_x += (15 * 5);
  }

  crab_x = 100;

  for (int i = 0; i < 11; i++) {
    this->spawn_alien(AlienVariant::Crab, crab_x, row_4);
    crab_x += (15 * 5);
  }

  float squid_x = 108;

  for (int i = 0; i < 11; i++) {
    this->spawn_alien(AlienVariant::Squid, squid_x, row_5);
    squid_x += (15 * 5);
  }
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

  for (auto & event: this->events) {
    this->handle_event(event);
  }

  Canvas::clear(this->renderer);

  for (auto & star: this->stars) { star->animate(); }

  if (!this->player->destroyed) { this->player->animate(); }

  for (auto & bullet: this->bullets) { bullet->animate(); }
  for (auto & alien: this->aliens) { alien->animate(); }

  this->status_bar->show();

  for (auto & bullet: this->bullets) {
    if (bullet->direction == -1) {
      for (auto & alien: this->aliens) {
        auto a = alien->hitbox; 
        auto b = bullet->hitbox;
  
        if (SDL_HasRectIntersectionFloat(&a, &b)) {
          bullet->destroyed = true;
          alien->destroyed = true;
        }
      }
    }
  }

  for (auto & bullet: this->bullets) {
    if (bullet->direction == 1) {
      auto a = this->player->hitbox; 
      auto b = bullet->hitbox;

      if (SDL_HasRectIntersectionFloat(&a, &b)) {
        bullet->destroyed = true;
        this->lives--;
        this->status_bar->ships--;

        if (this->lives == 0) this->player->destroyed = true;
      }
    }
  }

  for (auto & alien: this->aliens) {
    int blocking_aliens_count = 0;

    for (auto & other_alien: this->aliens) {
      if (
        (other_alien->y > alien->y) && (
          (
            ((other_alien->x < alien->x + alien->w) &&
            (other_alien->x > alien->x)) ||
            ((other_alien->x + other_alien->w > alien->x) &&
            (other_alien->x < alien->x + alien-> w))
          )
        )
      ) {
        blocking_aliens_count++;
      }
    }

    if (blocking_aliens_count == 0) {
      bool should_fire = rand() % 200 == 1;

      if (should_fire) {
        this->bullets.emplace_back(std::make_unique<Bullet>(
          this->renderer,
          alien->x + ((alien->w * Canvas::Pixel_Size) / 2),
          alien->y + alien->h + 5,
          1
        ));
      }
    }

    if (alien->destroyed) {
      switch (alien->variant) {
        case AlienVariant::Octopus:
          this->score += 10;
          break;
        case AlienVariant::Crab:
          this->score += 20;
          break;
        case AlienVariant::Squid:
          this->score += 30;
          break;
        default:
          break;
      }
  
      this->status_bar->score = this->score;
    }
  }

  SDL_RenderPresent(this->renderer);
  this->last_tick = current_tick;
}

void Game::shoot(float player_x, float player_y, float player_h, float player_w) {
  this->bullets.emplace_back(std::make_unique<Bullet>(
    this->renderer,
    player_x + ((player_w * Canvas::Pixel_Size) / 2),
    player_y - (player_h / 2),
    -1
  ));
};

void Game::spawn_alien(AlienVariant variant, float x, float y) {
  this->aliens.emplace_back(std::make_unique<Alien>(
    this->renderer,
    variant,
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
        this->shoot(this->player->x, this->player->y, this->player->h, this->player->w);
      }
      break;
    case SDL_EVENT_KEY_UP: 
      if (event->key.key == SDLK_LEFT || event->key.key == SDLK_RIGHT) {
        this->player->direction = 0;
      }
      break;
  };
};
