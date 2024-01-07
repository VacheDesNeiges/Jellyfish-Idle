#include "UIOctopusPanel.hpp"
#include "InputHandler.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "imgui.h"

void
UIOctopusPanel::render () const
{
  if (!ImGui::Begin ("Octopus", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  static bool showBoughtUpgrades = false;
  ImGui::Checkbox ("Show bought upgrades", &showBoughtUpgrades);

  for (const auto &upgradeID : UpgradeManager::UpgradesTypes)
    {
      if (showBoughtUpgrades
          || gData->getUpgradeView ()->isAvailableForBuying (upgradeID))
        {
          renderTradeButton (upgradeID);
        }
    }

  ImGui::End ();
}

void
UIOctopusPanel::renderTradeButton (UpgradeID id) const
{
  auto size = ImVec2 (300.f, 45.f);
  if (gData->getAchievementsView ()->isUnlocked (id))
    {
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
          std::string tooltipText = fmt::format (
              "{}", gData->getUpgradeView ()->getDescription (id));
          ImGui::Text ("%s", tooltipText.c_str ());
          ImGui::EndTooltip ();
        }

      ImGui::EndDisabled ();
    }
}
