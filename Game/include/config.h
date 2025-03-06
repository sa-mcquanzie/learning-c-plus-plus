#pragma once


namespace Window {
  [[maybe_unused]] static const char * Title = "Mr Rectangle";
  const int Width= 1600;
  const int Height = 800;
  const float F_Width= float(Width);
  const float F_Height = float(Height);
  const int Size = 150;
}

namespace Animation {
  const int TPS = 1000;
  const int FPS = TPS / 30;
}
