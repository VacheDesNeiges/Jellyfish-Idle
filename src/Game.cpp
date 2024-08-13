#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <gtest/gtest.h>
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
    UI.bindInputHandler(gameSystems.getInputHandler());
    UI.setAtlas(wrappedRenderer.loadTextures());
};

void Game::run(std::optional<std::string_view> option)
{
    if (std::filesystem::exists(SaveSystem::saveFileName) &&
        !(option.has_value() && option == "--noSave"))
    {
        gameSystems.loadSave(std::string(FilePaths::getPath()));
    }

    constexpr std::chrono::milliseconds interval(500);
    auto nextTick = std::chrono::high_resolution_clock::now() + interval;

    std::jthread eventHandler(&Game::eventThread, this);
    while (!done)
    {
        if (std::chrono::high_resolution_clock::now() >= nextTick)
        {
            gameSystems.gameTick();
            nextTick += interval;
        }
        renderFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    gameSystems.save();
}

void Game::renderFrame()
{
    wrappedRenderer.startRenderingNewFrame();
    UI.renderUI();
    wrappedRenderer.finalizeRenderingNewFrame();
}

void Game::eventThread()
{
    SDL_Event event;

    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            done = wrappedRenderer.processEvent(event);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}
