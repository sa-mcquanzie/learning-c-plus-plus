#include <cmath>
#include <iterator>
#include "canvas.hpp" 
#include "colour.hpp"
#include "config.hpp"
#include "entity.hpp"


Player::Player(
  SDL_Renderer * renderer
): Entity(renderer) {
  this->entity_type = EntityType::Player;
  this->renderer = renderer;
  this->sprite = sprite;
  this->visible = true;
  this->w = 13.0f;
  this->h = 8.0f;
  this->x = Window::F_Width / 2 - (this->w * Canvas::Pixel_Size);
  this->y = Battlefield::F_Height - (this->h * Canvas::Pixel_Size);
  this->speed = 10;
  this->direction = 0;
  this->colour = Colour::Red;
  this->destroyed = false;
  this->hitbox = {
    this->x,
    this->y,
    this->w * Canvas::Pixel_Size,
    this->h * Canvas::Pixel_Size
  };

  this->sprite = {
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  };
};

Player::~Player() {};

void Player::show() {
  float sprite_cols = int(this->w);
  float pixel_size = Canvas::Pixel_Size;

  if (this->sprite.size() > 0) {
    for (
      std::vector<int>::iterator i = std::begin(this->sprite);
      i != std::end(this->sprite);
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

        auto index = std::distance(this->sprite.begin(), i);
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

void Player::move() {
  float x_velocity = this->speed * this->direction;
  float new_x = this->x + x_velocity;

  if (
    (new_x <= (Window::F_Width - (this->w * Canvas::Pixel_Size) + 1)) &&
    (new_x >= 0)
  ) {
    this->x = new_x;
  }

  this->update_hitbox();
};

void Player::update_hitbox() {
  this->hitbox.x = this-> x;
  this->hitbox.y = this->y;
}
