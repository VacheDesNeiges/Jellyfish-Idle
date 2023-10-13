#pragma once

#include "UIManager.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include <chrono>
#include <memory>
#include <src/GameData/GameDataSynchronizer.hpp>

class Game

{
public:
  Game ();
  ~Game ();
  void run ();

private:
  void initialize ();

  SDL_Window *window;
  SDL_Renderer *renderer;
  ImGuiIO *io;

  std::unique_ptr<UIManager> UI;
  std::shared_ptr<GameDataSynchronizer> gameData;
};