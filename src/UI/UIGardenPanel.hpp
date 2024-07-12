#pragma once

#include "GameIDsTypes.hpp"
#include "UIElement.hpp"

class UIGardenPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderCulture (AquaCultureID) const;

  void displayCultureProduction (AquaCultureID) const;
  void displayCultureConsumption (AquaCultureID) const;
  void displayFieldsAssignmentArrows (const std::string &,
                                      AquaCultureID) const;
  void displayGrowAndStopButtons (AquaCultureID) const;
};