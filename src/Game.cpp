#include "Game.hpp"

#include "FilePaths.hpp"
#include "GameSystems.hpp"
#include "SaveSystem.hpp"

#include "UIUtils.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <gtest/gtest.h>
#include <linux/limits.h>
#include <memory>
#include <optional>
#include <string_view>
#include <system_error>
#include <thread>

Game::Game ()
{
  done = false;
  initialize ();
};

Game::~Game ()
{
  ImGui_ImplSDLRenderer2_Shutdown ();
  ImGui_ImplSDL2_Shutdown ();
  ImGui::DestroyContext ();

  SDL_DestroyTexture (backgroundPicture);
  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  SDL_Quit ();
}

void
Game::run (std::optional<std::string_view> option)
{
  constexpr std::chrono::milliseconds interval (500);
  auto nextTick = std::chrono::high_resolution_clock::now () + interval;

  if (std::filesystem::exists (SaveSystem::saveFileName)
      && !(option.has_value () && option == "--noSave"))
    {
      gameSystems->loadSave (std::string (FilePaths::getPath ()));
    }

  std::jthread eventHandler (&Game::eventThread, this);

  while (!done)
    {
      if (std::chrono::high_resolution_clock::now () >= nextTick)
        {
          gameSystems->gameTick ();
          nextTick += interval;
        }
      renderFrame ();
      std::this_thread::sleep_for (std::chrono::milliseconds (15));
    }
  gameSystems->save ();
}

void
Game::initialize ()
{
  // --------------- Code from ImGui
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
      std::cerr << "Error: %s\n" << SDL_GetError ();
      throw std::system_error ();
      abort ();
    }

#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint (SDL_HINT_IME_SHOW_UI, "1");
#endif

  auto window_flags
      = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  window = SDL_CreateWindow ("Jellyfish Idle", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  renderer = SDL_CreateRenderer (
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (renderer == nullptr)
    {
      SDL_Log ("Error creating SDL_Renderer!");
      throw std::system_error ();
    }

  IMGUI_CHECKVERSION ();
  ImGui::CreateContext ();
  io = &ImGui::GetIO ();
  (void)io;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark ();
  ImGui_ImplSDL2_InitForSDLRenderer (window, renderer);
  ImGui_ImplSDLRenderer2_Init (renderer);

  // --------------- Code from this project
  loadBackgroundImage ();
  loadFont ();
  UIUtils::setBaseUITheme ();

  UI = std::make_unique<UIManager> ();
  loadButtonImg ();
  gameSystems = std::make_unique<GameSystems> ();

  UI->bindGameData (gameSystems->getDataView (),
                    gameSystems->getInputHandler ());
}

void
Game::loadFont ()
{
  std::string path (FilePaths::getPath ());
  path += FilePaths::FontPath;
  io->Fonts->AddFontFromFileTTF (path.c_str (), 15);
}

void
Game::loadBackgroundImage ()
{
  SDL_Surface *surfaceIcon = SDL_LoadBMP ("./assets/jellyfish64.bmp");
  assert (surfaceIcon != nullptr);

  SDL_SetWindowIcon (window, surfaceIcon);
  SDL_FreeSurface (surfaceIcon);

  SDL_Surface *surface = SDL_LoadBMP ("./assets/otherjfish.bmp");
  assert (surface != nullptr);
  backgroundPicture = SDL_CreateTextureFromSurface (renderer, surface);
  SDL_FreeSurface (surface);
  assert (backgroundPicture != nullptr);
}

void
Game::loadButtonImg ()
{
  SDL_Surface *surface = SDL_LoadBMP ("./assets/loopButton.bmp");
  assert (surface != nullptr);
  auto texture = SDL_CreateTextureFromSurface (renderer, surface);
  SDL_FreeSurface (surface);
  assert (texture != nullptr);
  UI->loadTextures (texture);
}

void
Game::renderFrame ()
{
  ImGui_ImplSDLRenderer2_NewFrame ();
  ImGui_ImplSDL2_NewFrame ();
  ImGui::NewFrame ();

  UI->renderUI ();

  ImGui::Render ();
  SDL_RenderSetScale (renderer, io->DisplayFramebufferScale.x,
                      io->DisplayFramebufferScale.y);
  SDL_RenderClear (renderer);
  SDL_RenderCopy (renderer, backgroundPicture, nullptr, nullptr);

  ImGui_ImplSDLRenderer2_RenderDrawData (ImGui::GetDrawData (), renderer);

  SDL_RenderPresent (renderer);
}

bool
Game::processEvent (const SDL_Event &event)
{

  ImGui_ImplSDL2_ProcessEvent (&event);

  if (event.type == SDL_QUIT)
    return true;

  if (event.type == SDL_WINDOWEVENT
      && event.window.event == SDL_WINDOWEVENT_CLOSE
      && event.window.windowID == SDL_GetWindowID (window))
    return true;

  return false;
}

void
Game::eventThread ()
{
  SDL_Event event;

  while (!done)
    {
      while (SDL_PollEvent (&event))
        {
          done = processEvent (event);
        }
      std::this_thread::sleep_for (std::chrono::milliseconds (1));
    }
}