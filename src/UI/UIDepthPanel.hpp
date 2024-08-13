#pragma once
#include "UIElement.hpp"

class UIDepthPanel : public UIElement
{
  public:
    void render() const override;

  private:
    void displayDepthsRewards() const;
};