#include "Game.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <chrono>
#include <exception>
#include <memory>
#include <src/GameData/GameDataSynchronizer.hpp>
#include <stdexcept>
#include <stdio.h>
#include <system_error>

Game::Game () { initialize (); };

Game::~Game ()
{
  ImGui_ImplSDLRenderer2_Shutdown ();
  ImGui_ImplSDL2_Shutdown ();
  ImGui::DestroyContext ();

  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  SDL_Quit ();
}

void
Game::initialize ()
{
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)
      != 0)
    {
      printf ("Error: %s\n", SDL_GetError ());
      throw std::system_error ();
    }

#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint (SDL_HINT_IME_SHOW_UI, "1");
#endif

  auto window_flags
      = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow ("Jellyfish Idle", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  renderer = SDL_CreateRenderer (
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
    {
      SDL_Log ("Error creating SDL_Renderer!");
      throw std::system_error ();
    }

  IMGUI_CHECKVERSION ();
  ImGui::CreateContext ();
  io = &ImGui::GetIO ();
  (void)io;
  io->ConfigFlags
      |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io->ConfigFlags
      |= ImGuiConfigFlags_NavEnableGamepad;          // Enable Gamepad Controls
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

  ImGui::StyleColorsDark ();
  ImGui_ImplSDL2_InitForSDLRenderer (window, renderer);
  ImGui_ImplSDLRenderer2_Init (renderer);

  UI = std::make_unique<UIManager> ();
  gameData = std::make_shared<GameDataSynchronizer> ();
  UI->bindGameData (gameData);
}

void
Game::run ()
{
  const std::chrono::milliseconds interval (500);
  auto nextTick = std::chrono::high_resolution_clock::now () + interval;
  bool done = false;
  while (!done)
    {
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          ImGui_ImplSDL2_ProcessEvent (&event);
          if (event.type == SDL_QUIT)
            done = true;
          if (event.type == SDL_WINDOWEVENT
              && event.window.event == SDL_WINDOWEVENT_CLOSE
              && event.window.windowID == SDL_GetWindowID (window))
            done = true;
        }

      auto currentTime = std::chrono::high_resolution_clock::now ();
      if (currentTime >= nextTick)
        {
          gameData->gameTick ();
          nextTick += interval;
        }

      ImGui_ImplSDLRenderer2_NewFrame ();
      ImGui_ImplSDL2_NewFrame ();
      ImGui::NewFrame ();

      UI->renderUI ();

      ImGui::Render ();
      SDL_RenderSetScale (renderer, io->DisplayFramebufferScale.x,
                          io->DisplayFramebufferScale.y);
      SDL_RenderClear (renderer);
      ImGui_ImplSDLRenderer2_RenderDrawData (ImGui::GetDrawData ());
      SDL_RenderPresent (renderer);
    }
}