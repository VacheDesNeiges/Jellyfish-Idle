#include "UIBuildingsPanel.hpp"

#include "AchievementIDs.hpp"
#include "Building.hpp"
#include "InputHandler.hpp"
#include "UIUtils.hpp"

#include "imgui.h"
#include <fmt/format.h>

void
UIBuildingPanel::render () const
{
  if (!ImGui::Begin ("Buildings", nullptr,
                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  ImGui::SetCursorPosX (50);
  if (ImGui::Button ("Gather Sand", UIConstants::UIBuildingButtonSize))
    {
      inputHandler->gatherSand ();
    }

  bool odd = !renderJellyfishLuringButton ();
  if (!odd)
    ImGui::SetCursorPosX (50);

  using enum BuildingType;
  for (const auto &building : Building::BuildingTypes)
    {
      if (renderBuildingButton (building))
        {
          odd = !odd;
          ImGui::SetCursorPosX (50);
        }

      if (odd)
        ImGui::SameLine ();
    }

  ImGui::End ();
}

bool
UIBuildingPanel::renderBuildingButton (BuildingType building) const
{

  if (gData->getAchievementsView ()->isUnlocked (building))
    {
      ImGui::BeginDisabled (!gData->getBuildingsView ()->isBuyable (building));
      auto name = gData->getBuildingsView ()->getBuildingName (building);
      auto quantity
          = gData->getBuildingsView ()->getBuildingQuantity (building);
      std::string buttonText = fmt::format ("{} lvl {}", name, quantity);

      if (ImGui::Button (buttonText.c_str (),
                         UIConstants::UIBuildingButtonSize))
        {
          inputHandler->buy (building);
        }
      ImGui::EndDisabled ();
      setToolTip (building);

      return true;
    }
  return false;
}

void
UIBuildingPanel::setToolTip (BuildingType building) const
{
  ImGui::SetNextWindowSize ({ 300, -1 });

  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      ImGui::SeparatorText ("Description");
      ImGui::TextWrapped ("%s\n", gData->getBuildingsView ()
                                      ->getBuildingDescription (building)
                                      .c_str ());

      auto ressourcesNeeded
          = gData->getBuildingsView ()->getNextBuyCost (building);
      ImGui::SeparatorText ("Price");
      UIUtils::printCostsImGui (gData, ressourcesNeeded);

      ImGui::EndTooltip ();
    }
}

bool
UIBuildingPanel::renderJellyfishLuringButton () const
{
  ImGui::SameLine ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementIDs::JellyfishLuring))
    {
      ImGui::BeginDisabled (!gData->getJelliesView ()->canLure ());

      if (ImGui::Button ("Lure Jellyfish", UIConstants::UIBuildingButtonSize))
        {
          inputHandler->lureJellyfish ();
        }
      ImGui::EndDisabled ();
      ImGui::SetNextWindowSize ({ 300, -1 });

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled)
          && ImGui::BeginTooltip ())
        {
          ImGui::TextWrapped (
              "Allows you to use some food to lure a jellyfish");

          if (gData->getJelliesView ()->getMaxNumJellies ()
              == gData->getJelliesView ()->getNumJellies ())
            {
              ImGui::PushStyleColor (ImGuiCol_Text, UIColors::redText);
              ImGui::TextWrapped ("Not enough room to host more jellies");
              ImGui::PopStyleColor ();
            }

          ImGui::SeparatorText ("Price :");
          UIUtils::printCostsImGui (
              gData, { gData->getJelliesView ()->getLureCost () });

          ImGui::EndTooltip ();
        }

      return true;
    }
  return false;
}