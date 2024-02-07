#pragma once
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "InputHandler.hpp"

#include <memory>

class UIElement
{

public:
  UIElement () = default;
  virtual ~UIElement () = default;

  virtual void render () const = 0;

  void
  bindGameData (std::shared_ptr<GameDataView> viewPtr,
                std::shared_ptr<InputHandler> inputPtr)
  {
    this->gData = viewPtr;
    this->inputHandler = inputPtr;
  }

  std::shared_ptr<GameDataView> gData;
  std::shared_ptr<InputHandler> inputHandler;
};