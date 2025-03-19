#include "canvas.hpp"
#include "entity.hpp"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cmath>


Alien::Alien(
  SDL_Renderer * renderer,
  AlienVariant variant,
  float x,
  float y
): Entity(renderer, x, y)  {
  this->entity_type = EntityType::Alien;
  this->renderer = renderer;
  this->variant = variant;
  this->x = x;
  this->y = y;
  this->visible = true;
  this->colour = Colour::Green;
  if (this->variant == AlienVariant::Octopus) { this->w = 12.0f; }
  if (this->variant == AlienVariant::Crab) { this->w = 11.0f; }
  if (this->variant == AlienVariant::Squid) { this->w = 8.0f; }
  this->h = 8.0f;
  this->speed = 2.0f;
  this->hitbox = {
    this->x,
    this->y,
    this->w * Canvas::Pixel_Size,
    this->h * Canvas::Pixel_Size
  };
  this->sprite_current_frame = 0;
  this->sprite_total_frames = 2;
  this->animation_rate = 1000;
  this->last_animated = SDL_GetTicks();
  this->x_min = this->x - 100.0f;
  this->x_max = this->x + ((11 * Canvas::Pixel_Size) + 100.0f) - 5;
  this->y_max = this->y + (10 * Canvas::Pixel_Size);
  this->phase = AlienPhase::Strafing;
  this->direction = -1;
  this->can_fire = false;
  this->should_fire = false;

  if (this->variant == AlienVariant::Squid) {
    std::vector<int> frame1 = {
       0,  0,  0, 10, 10,  0,  0,  0,
       0,  0, 10, 10, 10, 10,  0,  0,
       0, 10, 10, 10, 10, 10, 10,  0,
      10, 10,  0, 10, 10,  0, 10, 10,
      10, 10, 10, 10, 10, 10, 10, 10,
       0, 10,  0, 10, 10,  0, 10,  0,
      10,  0,  0,  0,  0,  0,  0, 10,
       0, 10,  0,  0,  0,  0, 10,  0,
    };
  
    std::vector<int> frame2 = {
       0,  0,  0, 10, 10,  0,  0,  0,
       0,  0, 10, 10, 10, 10,  0,  0,
       0, 10, 10, 10, 10, 10, 10,  0,
      10, 10,  0, 10, 10,  0, 10, 10,
      10, 10, 10, 10, 10, 10, 10, 10,
       0,  0, 10,  0,  0, 10,  0,  0,
       0, 10,  0, 10, 10,  0, 10,  0,
      10,  0, 10,  0,  0, 10,  0, 10,
    };
  
    this->sprite = {frame1, frame2};
  }

  if (this->variant == AlienVariant::Crab) {
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
  }

  if (this->variant == AlienVariant::Octopus) {
    std::vector<int> frame1 = {
      0,0,0,0,3,3,3,3,0,0,0,0,
      0,3,3,3,3,3,3,3,3,3,3,0,
      3,3,3,3,3,3,3,3,3,3,3,3,
      3,3,3,0,0,3,3,0,0,3,3,3,
      3,3,3,3,3,3,3,3,3,3,3,3,
      0,0,0,3,3,0,0,3,3,0,0,0,
      0,0,3,3,0,3,3,0,3,3,0,0,
      3,3,0,0,0,0,0,0,0,0,3,3,
    };
  
    std::vector<int> frame2 = {
      0,0,0,0,3,3,3,3,0,0,0,0,
      0,3,3,3,3,3,3,3,3,3,3,0,
      3,3,3,3,3,3,3,3,3,3,3,3,
      3,3,3,0,0,3,3,0,0,3,3,3,
      3,3,3,3,3,3,3,3,3,3,3,3,
      0,0,3,3,3,0,0,3,3,3,0,0,
      0,3,3,0,0,3,3,0,0,3,3,0,
      0,0,3,3,0,0,0,0,3,3,0,0,
    };
  
    this->sprite = {frame1, frame2};
  } 
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
  if (this->phase == AlienPhase::Strafing) {
    if (this->direction == -1) {
      if (this->x <= this->x_min) {
        this->phase = AlienPhase::Advancing;
        this->direction = 1;
      } else {
        this->x += this->speed * this->direction;
      }
    } else {
      if (this->direction == 1) {
        if (this->x >= this->x_max) {
          this->phase = AlienPhase::Advancing;
          this->direction = -1;
        } else {
          this->x += this->speed * this->direction;
        }
      }
    }
  }

  if (this->phase == AlienPhase::Advancing) {
    if (this->y <= this->y_max) {
      this->y += 2;
    } else {
      this->y_max += 10 * Canvas::Pixel_Size;
      this->phase = AlienPhase::Strafing;
    }
  }

  this->update_hitbox();
};

void Alien::update_hitbox() {
  this->hitbox.x = this-> x;
  this->hitbox.y = this->y;
};
