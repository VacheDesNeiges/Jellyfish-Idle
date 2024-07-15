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

  for (const auto &ability : abilitiesView ()->getAbilityTypes ())
    {
      renderAbilityButton (ability);
    }

  ImGui::End ();
}

void
UIAbilitiesPanel::renderAbilityButton (AbilityType ability) const
{
  constexpr auto size = ImVec2 (300.f, 45.f);
  if (achievementsView ()->isUnlocked (ability))
    {

      if (ImGui::Button (abilitiesView ()->getAbilityName (ability).c_str (),
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
      ImGui::Text ("%s\n",
                   abilitiesView ()->getAbilityDescription (ability).c_str ());

      auto ressourcesNeeded = abilitiesView ()->getCost (ability);

      UIUtils::printCostsImGui (ressourcesView (), ressourcesNeeded);

      ImGui::EndTooltip ();
    }
}