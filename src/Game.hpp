#pragma once

#include "GameSystems.hpp"
#include "UIManager.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include <SDL2/SDL_render.h>
#include <chrono>
#include <memory>

class Game

{
public:
  Game ();
  ~Game ();
  void run ();

private:
  void initialize ();
  void loadFont ();
  void loadBackgroundImage ();
  void setImguiStyle () const;
  std::string getPath () const;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *backgroundPicture;
  ImGuiIO *io;

  std::unique_ptr<UIManager> UI;
  std::unique_ptr<GameSystems> gameSystems;
};