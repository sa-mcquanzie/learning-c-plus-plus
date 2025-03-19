#include "canvas.hpp"
#include "config.hpp"
#include "entity.hpp"


Bullet::Bullet(
  SDL_Renderer * renderer,
  float x,
  float y,
  float direction
): Entity(renderer, x, y)  {
  this->entity_type = EntityType::Bullet;
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->visible = true;
  this->colour = Colour::White;
  this->w = 3.0f;
  this->h = 30.0f;
  this->hitbox = {
    this->x,
    this->y,
    this->w * Canvas::Pixel_Size,
    this->h * Canvas::Pixel_Size
  };
  this->direction = direction;
};

void Bullet::show() {
  SDL_SetRenderDrawColor(
    this->renderer,
    this->colour.red,
    this->colour.green,
    this->colour.blue,
    this->colour.alpha
  );

  SDL_FRect fillRect = {this->x, this->y, this->w, this->h};
  SDL_RenderFillRect(this->renderer, &fillRect);
};

void Bullet::move() {
  this->y += 20.0f * this->direction;

  this->update_hitbox();

  if (
    this->y < 0 - this->h ||
    this->y >= Battlefield::F_Height
  ) {
    this->destroyed = true;
  }
};

void Bullet::update_hitbox() {
  this->hitbox.x = this-> x;
  this->hitbox.y = this->y;
}

Bullet::~Bullet() {};