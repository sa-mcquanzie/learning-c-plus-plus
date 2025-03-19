#include "config.hpp"
#include "entity.hpp"
#include <cmath>


Star::Star(
  SDL_Renderer * renderer
): Entity(renderer)  {
  this->entity_type = EntityType::Star;
  this->renderer = renderer;
  this->x = rand() % Window::Width;
  this->y = -20;
  this->visible = true;
  this->speed = 1.0f;
  this->alpha = rand() % 200;

  int types[20] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 2, 2, 2, 3
  };

  int type = types[rand() % 20];

  switch (type) {
    case 1:
      this->sprite = {
        0, 0,  0,
        0, 15, 0,
        0, 0,  0
      };
      break;
    case 2:
      this->sprite = {
         0, 15, 0,
        15, 15, 15,
         0, 15, 0
      };
      break;
    case 3:
      this->sprite = {
        15, 0,  15,
        0,  15,  0,
        15, 0,  15
      };
      break;
    default:
    break;
  }
};

Star::~Star() {};

void Star::show() {
  float pixels_width = 3;

  this->alpha = (this->alpha + 10 % 200);

  SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

  for (std::vector<int>::iterator i = std::begin(sprite); i != std::end(sprite); ++i) {
    if (*i != 0) {
      SDL_SetRenderDrawColor(
        this->renderer,
        Colour::Colour16[*i].red,
        Colour::Colour16[*i].green,
        Colour::Colour16[*i].blue,
        this->alpha
      );

      auto index = std::distance(sprite.begin(), i);
      float row = float(floor(index / pixels_width));
      float col = float(index % int(pixels_width));

      SDL_FRect fill_rect = {
        this->x + (col * 3),
        this->y + (row * 3),
        3,
        3
      };
      SDL_RenderFillRect(this->renderer, &fill_rect);
    }
  }
};

void Star::move() {
  this->y += this->speed;

  if (this->y > Window::Height) this->destroyed = true;
};
