#include "entity.hpp"
#include <SDL3/SDL_render.h>
#include <cmath>
#include <string>


Entity::Entity(
  SDL_Renderer * renderer,
  float x,
  float y
) {
  this->entity_type = EntityType::Base;
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->w = 0;
  this->h = 0;
  this->visible = true;
  this->destroyed = false;
};

Entity::Entity(
  SDL_Renderer * renderer
) {
  this->renderer = renderer;
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
  this->visible = false;
  this->destroyed = false;
};

Entity::~Entity() {};

void Entity::animate() {
  this->move();
  this->show();
};

std::string Entity::own_type() {
  return Entity::types[static_cast<int>(this->entity_type)];
};
