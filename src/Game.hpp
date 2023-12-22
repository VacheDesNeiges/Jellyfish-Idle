#pragma once

#include "GameSystems.hpp"
#include "UIManager.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
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
  std::string getPath () const;

  SDL_Window *window;
  SDL_Renderer *renderer;
  ImGuiIO *io;

  std::unique_ptr<UIManager> UI;
  std::unique_ptr<GameSystems> gameSystems;
};