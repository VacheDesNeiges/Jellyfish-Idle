#pragma once

#include "UIElement.hpp"
class UIBuildingPanel : public UIElement
{
  public:
    void render() const override;

  private:
    bool renderBuildingButton(BuildingType) const;
    bool renderJellyfishLuringButton() const;

    void setToolTip(BuildingType) const;
};
