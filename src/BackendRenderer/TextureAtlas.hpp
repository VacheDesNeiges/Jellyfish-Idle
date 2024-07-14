#pragma once
#include <SDL2/SDL_render.h>

struct TextureAtlas
{
  TextureAtlas () = default;
  ~TextureAtlas ();
  TextureAtlas (TextureAtlas &&) noexcept;
  TextureAtlas &operator= (TextureAtlas &&) noexcept;

  SDL_Texture *loopButton = nullptr;
};