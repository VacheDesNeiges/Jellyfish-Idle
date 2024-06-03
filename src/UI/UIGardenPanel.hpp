#pragma once

#include "AquaCulture.hpp"
#include "UIElement.hpp"

class UIGardenPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderCulture (AquaCultureID) const;
  void displayCultureCost (AquaCultureID) const;
};