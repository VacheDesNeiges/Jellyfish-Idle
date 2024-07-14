#pragma once

#include "GameSystems.hpp"
#include "RendererWrapper.hpp"
#include "UIManager.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <atomic>
#include <memory>
#include <optional>

class Game

{
public:
  Game ();
  ~Game () = default;
  Game (Game &) = delete;
  Game &operator= (Game &) = delete;

  void run (std::optional<std::string_view>);

private:
  void eventThread ();
  bool processEvent (const SDL_Event &) const;
  void renderFrame ();
  std::atomic<bool> done = false;

  std::unique_ptr<UIManager> UI;
  std::unique_ptr<GameSystems> gameSystems;
  RendererWrapper wrappedRenderer;
};