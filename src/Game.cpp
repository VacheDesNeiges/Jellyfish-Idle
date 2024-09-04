#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <linux/limits.h>

#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string_view>
#include <thread>

#include "FilePaths.hpp"
#include "GameSystems.hpp"
#include "SaveSystem.hpp"
#include "UIUtils.hpp"
#include "imgui_impl_sdl2.h"

Game::Game()
{
    wrappedRenderer.setBackgroundImage();
    wrappedRenderer.setFont();

    UIUtils::setBaseUITheme();
    ui.bindInputHandler(gameSystems.getInputHandler());
    ui.setAtlas(wrappedRenderer.loadTextures());
};

void Game::run(std::optional<std::string_view> option)
{
    if (std::filesystem::exists(SaveSystem::saveFileName) &&
        !(option.has_value() && option == "--noSave"))
    {
        gameSystems.loadSave(std::string(FilePaths::getPath()));
    }

    auto nextTick = std::chrono::high_resolution_clock::now() + frameInterval;
    std::jthread eventHandler(&Game::eventThread, this);
    while (!done)
    {
        if (std::chrono::high_resolution_clock::now() >= nextTick)
        {
            gameSystems.gameTick();
            nextTick += frameInterval;
        }
        renderFrame();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(frameRenderingInterval));
    }
    gameSystems.save();
}

void Game::renderFrame()
{
    wrappedRenderer.startRenderingNewFrame();
    ui.renderUI();
    wrappedRenderer.finalizeRenderingNewFrame();
}

void Game::eventThread()
{
    SDL_Event event;

    while (!done)
    {
        while (SDL_PollEvent(&event) > 0)
        {
            done = wrappedRenderer.processEvent(event);
        }
        std::this_thread::sleep_for(
            std::chrono::milliseconds(frameRenderingInterval));
    }
}
