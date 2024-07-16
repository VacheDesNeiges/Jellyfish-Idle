#pragma once

#include "UIElement.hpp"
class UIOctopusPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderTradeButton (UpgradeID) const;
  void renderQuestCard () const;
};