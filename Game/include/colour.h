#pragma once


struct Rgba {
  int red;
  int green;
  int blue;
  int alpha;
};

namespace Colour {
  const Rgba Background = {0, 0, 0, 255};
  const Rgba Red = {255, 0, 0, 255};
  const Rgba Green = {0, 255, 0, 255};
  const Rgba Blue = {0, 0, 255, 255};
  const Rgba White = {255, 255, 255, 255};

  const Rgba Colour16[16] = {
    {0, 0 ,0 ,0},               // 0: Black
    {127, 0, 0, 255},           // 1: Red
    {0, 147, 0, 255},           // 2: Green
    {252, 127, 0, 255},         // 3: Yellow
    {0, 0, 127, 255},           // 4: Blue
    {156, 0, 156, 255},         // 5: Magenta
    {0, 147, 147, 255},         // 6: Cyan
    {210, 210, 210, 255},       // 7: Silver
    {127, 127, 127, 255},       // 8: Grey
    {255, 0, 0, 255},           // 9: Bright Red
    {0, 252, 0, 255},           // 10: Bright Green
    {255, 255, 0, 255},         // 11: Bright Yellow
    {0, 0, 252, 255},           // 12: Bright Blue
    {255, 0, 255, 255},         // 13: Bright Magenta
    {0, 255, 255, 255},         // 14: Bright Cyan
    {255, 255, 255, 255},       // 15: White
  };
}