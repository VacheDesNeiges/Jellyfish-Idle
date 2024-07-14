#include "TextureAtlas.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

TextureAtlas::~TextureAtlas ()
{
  if (loopButton != nullptr)
    {
      SDL_DestroyTexture (loopButton);
      loopButton = nullptr;
    }
}

TextureAtlas::TextureAtlas (TextureAtlas &&other) noexcept
    : loopButton (other.loopButton)
{
  other.loopButton = nullptr;
}

TextureAtlas &
TextureAtlas::operator= (TextureAtlas &&other) noexcept
{
  if (this != &other)
    {
      loopButton = other.loopButton;
      other.loopButton = nullptr;
    }
  return *this;
}