#include "UIBuildingsPanel.hpp"
#include "AchievementDataView.hpp"
#include "Building.hpp"
#include "BuildingDataView.hpp"
#include "InputHandler.hpp"
#include "RessourceDataView.hpp"
#include "UIColors.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIBuildingPanel::render () const
{
  if (!ImGui::Begin ("Buildings", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("This is the Buildings tab!\n wiiiii");
  if (auto sz = ImVec2 (300.f, 45.0f); ImGui::Button ("GatherFood", sz))
    {
      inputHandler->gatherFood ();
    }

  ImGui::SameLine ();
  bool odd = true;

  using enum BuildingType;
  for (const auto &building : Building::BuildingTypes)
    {
      if (renderBuildingButton (building))
        odd = !odd;

      if (odd)
        ImGui::SameLine ();
    }

  ImGui::End ();
}

bool
UIBuildingPanel::renderBuildingButton (BuildingType building) const
{
  auto size = ImVec2 (300.f, 45.0f);

  if (gData->getAchievementsView ()->isUnlocked (building))
    {
      ImGui::BeginDisabled (!gData->getBuildingsView ()->isBuyable (building));
      if (ImGui::Button (gData->getBuildingsView ()
                             ->getBuildingDescription (building)
                             .c_str (),
                         size))
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

  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      ImVec4 textColor;
      auto ressourcesNeeded
          = gData->getBuildingsView ()->getNextBuyCost (building);

      ImGui::Text ("Price :");

      for (const auto &[ressource, cost] : ressourcesNeeded)
        {
          auto rquant
              = gData->getRessourcesView ()->getRessourceQuantity (ressource);
          auto ressourceName
              = gData->getRessourcesView ()->getRessourceName (ressource);

          if (cost > gData->getRessourcesView ()->getRessourceMaxQuantity (
                  ressource))
            {
              textColor = UIColors::redText;
            }
          else if (cost < rquant)
            {
              textColor = UIColors::greenText;
            }
          else
            {
              textColor = UIColors::greyText;
            }
          ImGui::TextColored (
              textColor, "%s",
              fmt::format ("\n{} : {:.2f}/{:.2f}", ressourceName, rquant, cost)
                  .c_str ());
        }

      ImGui::EndTooltip ();
    }
}
