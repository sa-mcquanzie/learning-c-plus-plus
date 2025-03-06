#include "entity.h"


Bullet::Bullet(
  SDL_Renderer * renderer,
  float x,
  float y
): Entity(renderer, x, y)  {
  this->entity_type = EntityType::Bullet;
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->visible = true;
  this->colour = Colour::White;
  this->w = 10.0f;
  this->h = 10.0f;
  this->hitbox = { this->x, this->y, this->w, this->h };
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
  this->y -= 20.0f;

  this->update_hitbox();

  if (this->y < 0 - this->h) this->destroyed = true;
};

void Bullet::update_hitbox() {
  this->hitbox.x = this-> x;
  this->hitbox.y = this->y;
}

Bullet::~Bullet() {};