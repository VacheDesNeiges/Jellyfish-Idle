#include "UIOctopusPanel.hpp"

#include "InputHandler.hpp"
#include "UIUtils.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIOctopusPanel::render () const
{
  if (!ImGui::Begin ("Octopus", nullptr,
                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  static bool showBoughtUpgrades = false;
  ImGui::Checkbox ("Show bought upgrades", &showBoughtUpgrades);

  for (const auto &upgradeID : UpgradeManager::UpgradesTypes)
    {
      if (showBoughtUpgrades)
        {
          if (gData->getUpgradeView ()->isBought (upgradeID))
            renderTradeButton (upgradeID);
        }
      else
        {
          if (gData->getUpgradeView ()->isAvailableForBuying (upgradeID)
              && gData->getAchievementsView ()->isUnlocked (upgradeID))

            renderTradeButton (upgradeID);
        }
    }

  ImGui::End ();
}

void
UIOctopusPanel::renderTradeButton (UpgradeID id) const
{
  auto size = ImVec2 (300.f, 45.f);

  ImGui::BeginDisabled (!gData->getUpgradeView ()->isBuyable (id));
  std::string buttonText
      = fmt::format ("{}\n", gData->getUpgradeView ()->getName (id));

  if (ImGui::Button (buttonText.c_str (), size))
    {
      inputHandler->buy (id);
    }
  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      std::string tooltipText
          = fmt::format ("{}", gData->getUpgradeView ()->getDescription (id));
      ImGui::Text ("%s", tooltipText.c_str ());

      auto cost = gData->getUpgradeView ()->getCost (id);
      UIUtils::printCostsImGui (gData, cost);

      ImGui::EndTooltip ();
    }

  ImGui::EndDisabled ();
}
