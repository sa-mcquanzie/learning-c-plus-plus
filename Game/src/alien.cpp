#include "canvas.h"
#include "config.h"
#include "entity.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cmath>


Alien::Alien(
  SDL_Renderer * renderer,
  float x,
  float y
): Entity(renderer, x, y)  {
  this->entity_type = EntityType::Alien;
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->visible = true;
  this->colour = Colour::Green;
  this->w = 11.0f;
  this->h = 8.0f;
  this->speed = 5.0f;
  this->hitbox = {this->x, this->y, this->w * 5, this->h * 5};
  this->sprite_current_frame = 0;
  this->sprite_total_frames = 2;
  this->animation_rate = 1000;
  this->last_animated = SDL_GetTicks();

  int directions[2] = {1, -1};
  this->direction = directions[rand() % 2];

  std::vector<int> frame1 = {
    0,0,6,0,0,0,0,0,6,0,0,
    0,0,0,6,0,0,0,6,0,0,0,
    0,0,6,6,6,6,6,6,6,0,0,
    0,6,6,0,6,6,6,0,6,6,0,
    6,6,6,6,6,6,6,6,6,6,6,
    6,0,6,6,6,6,6,6,6,0,6,
    6,0,6,0,0,0,0,0,6,0,6,
    0,0,0,6,6,0,6,6,0,0,0,
  };

  std::vector<int> frame2 = {
    0,0,6,0,0,0,0,0,6,0,0,
    6,0,0,6,0,0,0,6,0,0,6,
    6,0,6,6,6,6,6,6,6,0,6,
    6,6,6,0,6,6,6,0,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,
    0,0,6,6,6,6,6,6,6,0,0,
    0,0,6,0,0,0,0,0,6,0,0,
    0,6,0,0,0,0,0,0,0,6,0,
  };

  this->sprite = {frame1, frame2};
};

Alien::~Alien() {};

void Alien::show() {
  Uint64 current_tick = SDL_GetTicks();

  if (current_tick - this->last_animated > this->animation_rate) {
    this->sprite_current_frame = (this->sprite_current_frame + 1) % this->sprite_total_frames;
    this->last_animated = current_tick;
  }

  float sprite_cols = int(this->w);
  float pixel_size = Canvas::Pixel_Size;
  auto current_sprite = this->sprite[sprite_current_frame];

  if (current_sprite.size() > 0) {
    for (
      std::vector<int>::iterator i = std::begin(current_sprite);
      i != std::end(current_sprite);
      ++i
    ) {
      if (*i != 0) {
        SDL_SetRenderDrawColor(
          this->renderer,
          Colour::Colour16[*i].red,
          Colour::Colour16[*i].green,
          Colour::Colour16[*i].blue,
          Colour::Colour16[*i].alpha
        );

        auto index = std::distance(current_sprite.begin(), i);
        float row = float(floor(index / sprite_cols));
        float col = float(index % int(sprite_cols));

        SDL_FRect fill_rect = {
          this->x + (col * pixel_size),
          this->y + (row * pixel_size),
          pixel_size,
          pixel_size
        };

        SDL_RenderFillRect(this->renderer, &fill_rect);
      }
    }
  }
};

void Alien::move() {
  if (
    (this->direction == 1 && this->x > (Window::F_Width - (this->w * Canvas::Pixel_Size))) ||
    (this->direction == -1 && this->x == 0)
  ) {
    this->direction = -this->direction;
  }

  float x_velocity = this->speed * this->direction;

  this->x += x_velocity;
  this->y += 1;

  this->update_hitbox();
};

void Alien::update_hitbox() {
  this->hitbox.x = this-> x;
  this->hitbox.y = this->y;
};
