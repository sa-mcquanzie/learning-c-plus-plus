#pragma once
#include "colour.hpp"
#include <SDL3/SDL_render.h>


namespace Canvas {
  const int Pixel_Size = 5;
  void set_draw_colour(SDL_Renderer * renderer, Rgba colour);
  void clear(SDL_Renderer * renderer);
}
