#pragma once
#include "GameDataAccess.hpp"
#include "GameSystems.hpp"
#include "InputHandler.hpp"

#include <SDL2/SDL_render.h>
#include <memory>

class UIElement : public GameDataAccess
{

  public:
    UIElement() = default;
    virtual ~UIElement() = default;

    virtual void render() const = 0;

    void bindInputHandler(std::shared_ptr<InputHandler> inputPtr)
    {
        this->inputHandler = std::move(inputPtr);
    }

    std::shared_ptr<InputHandler> inputHandler;

    SDL_Texture *loopButtonTexture = nullptr;
};
