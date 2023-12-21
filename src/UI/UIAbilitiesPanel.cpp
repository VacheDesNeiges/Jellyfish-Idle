#include "UIAbilitiesPanel.hpp"
#include "AbilityDataView.hpp"
#include "InputHandler.hpp"
#include "imgui.h"

void
UIAbilitiesPanel::render () const
{
  if (ImGui::BeginTabItem ("Insight"))
    {
      using enum AbilityType;
      if (ImGui::Button (gData->getAbilitiesView ()
                             ->getAbilityName (CallThunder)
                             .c_str ()))
        {
          inputHandler->useAbility (CallThunder);
        }

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip ("%s", gData->getAbilitiesView ()
                                       ->getAbilityDescription (CallThunder)
                                       .c_str ());
        }

      ImGui::Text ("Insight Tab");
      ImGui::EndTabItem ();
    }
}