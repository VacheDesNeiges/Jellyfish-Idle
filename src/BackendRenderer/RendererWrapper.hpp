#pragma once

#include "TextureAtlas.hpp"
#include "imgui.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

class RendererWrapper
{
public:
  RendererWrapper ();
  ~RendererWrapper ();

  void startRenderingNewFrame () const;
  void finalizeRenderingNewFrame ();
  bool processEvent (const SDL_Event &);

  void setBackgroundImage (const std::string &);
  void setFont (const std::string &);
  TextureAtlas loadTextures ();

private:
  void initializeSDL ();
  void initializeImgui ();

  SDL_Window *window;
  SDL_Renderer *renderer;
  ImGuiIO *io;

  SDL_Texture *backgroundPicture;
};