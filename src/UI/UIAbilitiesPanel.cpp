#include "UIAbilitiesPanel.hpp"
#include "AbilityDataView.hpp"
#include "AbilityManager.hpp"
#include "AchievementDataView.hpp"
#include "InputHandler.hpp"
#include "InsightAbility.hpp"
#include "RessourceDataView.hpp"
#include "UIColors.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIAbilitiesPanel::render () const
{
  if (!ImGui::Begin ("Abilities", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  for (const auto &ability : InsightAbility::AbilitiesTypes)
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
  using enum AbilityType;
  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      ImGui::Text ("%s\n", gData->getAbilitiesView ()
                               ->getAbilityDescription (ability)
                               .c_str ());

      ImGui::Text ("\nPrice : ");

      auto ressourcesNeeded = gData->getAbilitiesView ()->getCost (ability);

      ImVec4 textColor;

      for (const auto &[ressource, cost] : ressourcesNeeded)
        {
          auto requestedQuantity
              = gData->getRessourcesView ()->getRessourceQuantity (ressource);
          auto ressourceName
              = gData->getRessourcesView ()->getRessourceName (ressource);

          if (cost > gData->getRessourcesView ()->getRessourceMaxQuantity (
                  ressource))
            {
              textColor = UIColors::redText;
            }
          else if (cost < requestedQuantity)
            {
              textColor = UIColors::greenText;
            }
          else
            {
              textColor = UIColors::greyText;
            }
          ImGui::TextColored (textColor, "%s",
                              fmt::format ("{} : {:.2f}/{:.2f}", ressourceName,
                                           requestedQuantity, cost)
                                  .c_str ());
        }

      ImGui::EndTooltip ();
    }
}