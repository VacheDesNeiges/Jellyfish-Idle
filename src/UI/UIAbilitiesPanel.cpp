#include "UIAbilitiesPanel.hpp"
#include "UIUtils.hpp"
#include "imgui.h"

void
UIAbilitiesPanel::render () const
{
  if (!ImGui::Begin ("Abilities", nullptr,
                     ImGuiWindowFlags_NoFocusOnAppearing
                         & ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  for (const auto &ability : gData->getAbilitiesView ()->getAbilityTypes ())
    {
      renderAbilityButton (ability);
    }

  ImGui::End ();
}

void
UIAbilitiesPanel::renderAbilityButton (AbilityType ability) const
{
  constexpr auto size = ImVec2 (300.f, 45.f);
  if (gData->getAchievementsView ()->isUnlocked (ability))
    {

      if (ImGui::Button (
              gData->getAbilitiesView ()->getAbilityName (ability).c_str (),
              size))
        {
          inputHandler->useAbility (ability);
        }

      setToolTip (ability);
    }
}

void
UIAbilitiesPanel::setToolTip (AbilityType ability) const
{
  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      ImGui::Text ("%s\n", gData->getAbilitiesView ()
                               ->getAbilityDescription (ability)
                               .c_str ());

      auto ressourcesNeeded = gData->getAbilitiesView ()->getCost (ability);

      UIUtils::printCostsImGui (gData, ressourcesNeeded);

      ImGui::EndTooltip ();
    }
}