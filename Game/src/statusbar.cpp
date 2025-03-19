#include "canvas.hpp"
#include "colour.hpp"
#include "config.hpp"
#include "entity.hpp"
#include <SDL3/SDL_render.h>
#include <cmath>


StatusBar::StatusBar(SDL_Renderer * renderer): Entity(renderer) {
  this->entity_type = EntityType::StatusBar;
  this->renderer = renderer;
  this->x = 0;
  this->y = Battlefield::F_Height;
  this->w = Battlefield::F_Width;
  this->h = 100.0f;
  this->score = 0;
  this->ships = 2;

  SDL_FRect* rect = new SDL_FRect(
    0,
    Battlefield::F_Height,
    Battlefield::F_Width,
    Battlefield::F_Height
  );

  this->rect = rect;
};

StatusBar::~StatusBar() {
  delete this->rect;
};

void StatusBar::show() {
  Canvas::set_draw_colour(this->renderer, Colour::Black);

  SDL_RenderFillRect(this->renderer, this->rect);

  Canvas::set_draw_colour(this->renderer, Colour::White);

  SDL_RenderLine(
    this->renderer,
    0,
    Battlefield::F_Height,
    Battlefield::F_Width,
    Battlefield::F_Height
  );

  char str[20];  
  sprintf(str,"%d",this->score);
  SDL_RenderDebugText(this->renderer, 20, this->y + 10, str);

  int player_sprite[104] = {
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  };

  float sprite_cols = 13;
  float pixel_size = Canvas::Pixel_Size;
  int index = 0;
  int ship_start_x = 10;

  for (int n = 0; n < this->ships; ++n) {
    for (auto i : player_sprite) {
      if (i != 0) {
        SDL_SetRenderDrawColor(
          this->renderer,
          Colour::Colour16[i].red,
          Colour::Colour16[i].green,
          Colour::Colour16[i].blue,
          Colour::Colour16[i].alpha
        );
  
        float row = float(floor(index / sprite_cols));
        float col = float(index % int(sprite_cols));
  
        SDL_FRect fill_rect = {
          ship_start_x + (col * pixel_size),
          this->y + 50 + (row * pixel_size),
          pixel_size,
          pixel_size
        };
  
        SDL_RenderFillRect(this->renderer, &fill_rect);
      }
  
      index++;
    }

    index = 0;
    ship_start_x += 100;
  }
};

void StatusBar::move() {};
