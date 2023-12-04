#include "Game.hpp"
#include "GameDataSynchronizer.hpp"
#include "SaveSystem.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <chrono>
#include <exception>
#include <filesystem>
#include <linux/limits.h>
#include <memory>
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

  ImGuiStyle &style = ImGui::GetStyle ();
  style.FrameRounding = 12.f;
  style.FramePadding = { 20.f, 3.f };
  style.WindowRounding = 12.f;
  style.WindowMenuButtonPosition = ImGuiDir_None;

  ImVec4 *colors = ImGui::GetStyle ().Colors;
  colors[ImGuiCol_WindowBg] = ImVec4 (0.01f, 0.02f, 0.06f, 0.94f);
  colors[ImGuiCol_PopupBg] = ImVec4 (0.13f, 0.19f, 0.26f, 0.94f);
  colors[ImGuiCol_Button] = ImVec4 (0.31f, 0.76f, 0.83f, 0.41f);
  colors[ImGuiCol_ButtonHovered] = ImVec4 (0.20f, 0.49f, 0.50f, 1.00f);
  // TODO : customize in a function

  // TODO : Load font in a function
  std::string path = getPath ();
  std::cout << path << "\n";
  path += "/assets/font/OpenSans-Bold.ttf";
  io->Fonts->AddFontFromFileTTF (path.c_str (), 17);

  // Game systems part below -------------------

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
  if (std::filesystem::exists (SaveSystem::saveFileName))
    gameData->loadSave (getPath ());

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

      if (std::chrono::high_resolution_clock::now () >= nextTick)
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
  gameData->save ();
}

std::string
Game::getPath () const
{
  char buff[PATH_MAX];
  ssize_t len = ::readlink ("/proc/self/exe", buff, PATH_MAX - 1);
  if (len != -1)
    {
      buff[len] = '\0';
      std::string ret (buff);
      std::size_t found = ret.rfind ('/');
      if (found != std::string::npos)
        ret = ret.substr (0, found);
      return ret;
    }
  assert (false);
}