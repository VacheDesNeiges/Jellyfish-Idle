#pragma once

#include "GameSystems.hpp"
#include "UIManager.hpp"
#include "imgui.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <atomic>
#include <memory>
#include <optional>

class Game

{
public:
  Game ();
  ~Game ();
  Game (Game &) = delete;
  Game &operator= (Game &) = delete;

  void run (std::optional<std::string_view>);

private:
  void initialize ();
  void loadFont ();
  void loadButtonImg ();
  void loadBackgroundImage ();
  void eventThread ();
  bool processEvent (const SDL_Event &);
  void renderFrame ();

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *backgroundPicture;
  ImGuiIO *io;

  std::atomic<bool> done;

  std::unique_ptr<UIManager> UI;
  std::unique_ptr<GameSystems> gameSystems;
};