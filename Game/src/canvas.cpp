#include "canvas.hpp"
#include "colour.hpp"
#include <SDL3/SDL_render.h>


void Canvas::set_draw_colour(SDL_Renderer * renderer, Rgba colour) {
  SDL_SetRenderDrawColor(renderer, colour.red,colour.green, colour.blue, colour.alpha);
}

void Canvas::clear(SDL_Renderer * renderer) {
  Canvas::set_draw_colour(renderer, Colour::Background);
  SDL_RenderClear(renderer);
}