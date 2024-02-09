#pragma once
#include "UIElement.hpp"

class UIRessourcesPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderRessources () const;
  void renderManufacturedRessources () const;
};
