#include "UIBuildingsPanel.hpp"
#include "AchievementDataView.hpp"
#include "Building.hpp"
#include "BuildingDataView.hpp"
#include "InputHandler.hpp"
#include "RessourceDataView.hpp"
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
  if (auto sz = ImVec2 (300.f, 20.0f); ImGui::Button ("GatherFood", sz))
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
  auto sz = ImVec2 (300.f, 20.0f);

  if (gData->getAchievementsView ()->isUnlocked (building))
    {

      ImGui::BeginDisabled (!gData->getBuildingsView ()->isBuyable (building));
      if (ImGui::Button (gData->getBuildingsView ()
                             ->getBuildingDescription (building)
                             .c_str (),
                         sz))
        {
          inputHandler->buy (building);
        }
      ImGui::EndDisabled ();

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          displayToolTip (building);
        }
      return true;
    }
  return false;
}

void
UIBuildingPanel::displayToolTip (BuildingType building) const
{
  auto ressourcesNeeded
      = gData->getBuildingsView ()->getNextBuyCost (building);

  std::string tooltip = "Price :";

  for (const auto &[ressource, cost] : ressourcesNeeded)
    {
      auto ressourceName
          = gData->getRessourcesView ()->getRessourceName (ressource);

      tooltip += fmt::format ("\n{} : {:.2f}", ressourceName, cost);
    }

  ImGui::SetTooltip ("%s", tooltip.c_str ());
}
