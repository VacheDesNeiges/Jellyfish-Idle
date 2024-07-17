#pragma once

#include "TextureAtlas.hpp"
#include "imgui.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class RendererWrapper
{
public:
  RendererWrapper ();
  ~RendererWrapper ();

  void startRenderingNewFrame () const;
  void finalizeRenderingNewFrame ();
  bool processEvent (const SDL_Event &);

  void setBackgroundImage ();
  void setFont ();
  TextureAtlas loadTextures ();

private:
  void initializeSDL ();
  void initializeImgui ();

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  ImGuiIO *io = nullptr;

  SDL_Texture *backgroundPicture = nullptr;
};