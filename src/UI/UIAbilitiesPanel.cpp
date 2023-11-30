#include "UIAbilitiesPanel.hpp"
#include "imgui.h"

void
UIAbilitiesPanel::render () const
{
  if (ImGui::BeginTabItem ("Insight"))
    {
      using enum AbilityType;
      if (ImGui::Button (gData->getAbilityName (CallThunder).c_str ()))
        {
          gData->useAbility (CallThunder);
        }

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip (
              "%s", gData->getAbilityDescription (CallThunder).c_str ());
        }

      ImGui::Text ("Insight Tab");
      ImGui::EndTabItem ();
    }
}