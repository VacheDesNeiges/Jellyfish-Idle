#pragma once

#include "UIElement.hpp"

class UIGardenPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderCulture (AquaCultureID) const;

  void displayCultureProduction (AquaCultureID) const;
  void displayFieldsAssignmentArrows (const std::string &,
                                      AquaCultureID) const;
  void displayCultureCost (AquaCultureID) const;
  void displayGrowAndStopButtons (AquaCultureID) const;
};