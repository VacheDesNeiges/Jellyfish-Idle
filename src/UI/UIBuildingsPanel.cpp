#include "UIBuildingsPanel.hpp"
#include "Building.hpp"
#include "imgui.h"

void
UIBuildingPanel::render () const
{
  if (ImGui::BeginTabItem ("Buildings"))
    {
      ImGui::Text ("This is the Buildings tab!\n wiiiii");
      if (auto sz = ImVec2 (300.f, 20.0f); ImGui::Button ("GatherFood", sz))
        {
          gData->gatherFood ();
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

      ImGui::EndTabItem ();
    }
}

bool
UIBuildingPanel::renderBuildingButton (BuildingType building) const
{
  auto sz = ImVec2 (300.f, 20.0f);

  if (gData->isUnlocked (building))
    {

      ImGui::BeginDisabled (!gData->isBuyable (building));
      if (ImGui::Button (gData->getBuildingDescription (building).c_str (),
                         sz))
        {
          gData->buy (building);
        }
      ImGui::EndDisabled ();
      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip (
              "%s", gData->getAdvancedBuildingDescription (building).c_str ());
        }

      return true;
    }
  return false;
}