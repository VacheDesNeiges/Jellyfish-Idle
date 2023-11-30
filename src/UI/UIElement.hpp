#pragma once
#include "GameDataSynchronizer.hpp"
#include <memory>

class UIElement
{

public:
  UIElement () = default;
  virtual ~UIElement () = default;

  virtual void render () const = 0;

  void
  bindGameData (std::shared_ptr<GameDataSynchronizer> ptr)
  {
    this->gData = ptr;
  }

  std::shared_ptr<GameDataSynchronizer> gData;
};