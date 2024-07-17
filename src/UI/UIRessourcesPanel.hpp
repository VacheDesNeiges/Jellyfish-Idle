#pragma once
#include "UIElement.hpp"

class UIRessourcesPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderJfishNumbers () const;
  void renderRessources () const;
  void renderManufacturedRessources () const;
  void renderRessource (RessourceType, bool hasMaxQuantity = false) const;
  void setupColumns () const;
};
