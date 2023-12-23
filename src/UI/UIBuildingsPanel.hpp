#pragma once

#include "Building.hpp"
#include "UIElement.hpp"
class UIBuildingPanel : public UIElement
{
public:
  void render () const override;

private:
  bool renderBuildingButton (BuildingType) const;
  void displayToolTip (BuildingType) const;
};