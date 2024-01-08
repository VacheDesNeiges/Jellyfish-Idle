#include "UIBuildingsPanel.hpp"
#include "Building.hpp"
#include "GameDataView.hpp"
#include "InputHandler.hpp"
#include "UIUtils.hpp"
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
  if (constexpr auto sz = ImVec2 (300.f, 45.0f);
      ImGui::Button ("GatherFood", sz))
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
  constexpr auto size = ImVec2 (300.f, 45.0f);

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
      auto ressourcesNeeded
          = gData->getBuildingsView ()->getNextBuyCost (building);

      UIUtils::printCostsImGui (gData, ressourcesNeeded);

      ImGui::EndTooltip ();
    }
}
