#pragma once
#include "InsightAbility.hpp"
#include "UIElement.hpp"

class UIAbilitiesPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderAbilityButton (AbilityType) const;
  void setToolTip (AbilityType) const;
};
