#pragma once

#include "AquaCulture.hpp"
#include "UIElement.hpp"

class UIGardenPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderCulture (AquaCultureID) const;

  void displayCultureProduction (const std::string &, AquaCultureID) const;
  void displayFieldsAssignmentArrows (const std::string &,
                                      AquaCultureID) const;
  void displayCultureCost (AquaCultureID) const;
  void displayStartAndCancelButtons (AquaCultureID) const;
  void displayProgressBar (AquaCultureID) const;
};