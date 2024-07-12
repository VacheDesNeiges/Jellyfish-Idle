#include "Game.hpp"

#include "FilePaths.hpp"
#include "GameSystems.hpp"
#include "SaveSystem.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cassert>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <gtest/gtest.h>
#include <linux/limits.h>
#include <memory>
#include <optional>
#include <string_view>
#include <system_error>

Game::Game () { initialize (); };

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
  bool done = false;

  if (std::filesystem::exists (SaveSystem::saveFileName)
      && !(option.has_value () && option == "--noSave"))
    {
      gameSystems->loadSave (std::string (FilePaths::getPath ()));
    }

  while (!done)
    {
      SDL_Event event;

      while (SDL_PollEvent (&event))
        {
          done = processEvent (event);
        }

      if (std::chrono::high_resolution_clock::now () >= nextTick)
        {
          gameSystems->gameTick ();
          nextTick += interval;
        }

      renderFrame ();
    }
  gameSystems->save ();
}

void
Game::initialize ()
{
  // --------------- Code from ImGui
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)
      != 0)
    {
      std::cerr << "Error: %s\n" << SDL_GetError ();
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
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark ();
  ImGui_ImplSDL2_InitForSDLRenderer (window, renderer);
  ImGui_ImplSDLRenderer2_Init (renderer);

  // --------------- Code from this project
  loadBackgroundImage ();
  loadFont ();
  setImguiStyle ();

  UI = std::make_unique<UIManager> ();
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
Game::setImguiStyle () const
{
  ImGuiStyle &style = ImGui::GetStyle ();
  style.SeparatorTextAlign = { 0.5, 0.5 };
  style.FrameRounding = 5.f;
  style.FramePadding = { 20.f, 3.f };
  style.WindowRounding = 5.f;
  style.WindowMenuButtonPosition = ImGuiDir_None;
  style.TabBarBorderSize = 0;
  style.TabRounding = 0;

  ImVec4 *colors = ImGui::GetStyle ().Colors;

  colors[ImGuiCol_Text] = ImVec4 (1, 1, 1, 1);

  colors[ImGuiCol_ModalWindowDimBg] = ImVec4 (0.123f, 0.687f, 0.493f, 0.350f);

  colors[ImGuiCol_WindowBg] = ImVec4 (0.010f, 0.019f, 0.060f, 0.000f);
  colors[ImGuiCol_PopupBg] = ImVec4 (0.2f, 0.2f, 0.2f, 0.8f);
  colors[ImGuiCol_Button] = ImVec4 (0.069f, 0.071f, 0.109f, 1.000f);
  colors[ImGuiCol_ButtonHovered] = ImVec4 (0.642f, 0.000f, 0.116f, 1.000f);
  colors[ImGuiCol_ButtonActive] = ImVec4 (0.896f, 0.000f, 0.162f, 1.000f);

  colors[ImGuiCol_TitleBg] = ImVec4 (0.000f, 0.000f, 0.000f, 0.000f);
  colors[ImGuiCol_TitleBgActive] = ImVec4 (0.000f, 0.000f, 0.000f, 0.000f);
  colors[ImGuiCol_Separator] = ImVec4 (0.133f, 0.000f, 0.000f, 0.827f);

  colors[ImGuiCol_FrameBg] = ImVec4 (0.134f, 0.000f, 0.000f, 0.826f);
  colors[ImGuiCol_PlotHistogram] = ImVec4 (0.796f, 0.039f, 0.176f, 0.494f);

  colors[ImGuiCol_TitleBgActive] = ImVec4 (0.000f, 0.000f, 0.000f, 0.000f);

  colors[ImGuiCol_TabUnfocused] = ImVec4 (0.134f, 0.000f, 0.000f, 0.826f);
  colors[ImGuiCol_TabUnfocusedActive]
      = ImVec4 (0.796f, 0.039f, 0.176f, 0.494f);

  colors[ImGuiCol_TabActive] = ImVec4 (0.796f, 0.039f, 0.176f, 0.494f);

  colors[ImGuiCol_Tab] = ImVec4 (0.133f, 0.000f, 0.000f, 0.827f);
  colors[ImGuiCol_TabHovered] = ImVec4 (0.896f, 0.000f, 0.162f, 1.000f);
}

void
Game::loadBackgroundImage ()
{
  SDL_Surface *surface = SDL_LoadBMP ("./assets/otherjfish.bmp");
  assert (surface != nullptr);
  backgroundPicture = SDL_CreateTextureFromSurface (renderer, surface);
  SDL_FreeSurface (surface);
  assert (backgroundPicture != nullptr);
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