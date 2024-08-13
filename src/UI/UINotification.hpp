#pragma once
#include "UIElement.hpp"

class UINotification : public UIElement
{
  public:
    void render() const override;

  private:
    void renderNotification();
};