#pragma once


namespace Window {
  [[maybe_unused]] static const char * Title = "Mr Rectangle";
  const int Width = 1055;
  const int Height = 1055;
  const float F_Width= float(Width);
  const float F_Height = float(Height);
}

namespace Battlefield {
  const int Width = Window::Width;
  const int Height = Window::Height - 100;
  const float F_Width= float(Width);
  const float F_Height = float(Height);
}

namespace Animation {
  const int TPS = 1000;
  const int FPS = TPS / 30;
}
