#include "UIOctopusPanel.hpp"

#include "UIUtils.hpp"
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

  for (const auto &upgradeID : upgradeView ()->getUpgradesTypes ())
    {
      if (showBoughtUpgrades)
        {
          if (upgradeView ()->isBought (upgradeID))
            renderTradeButton (upgradeID);
        }
      else
        {
          if (upgradeView ()->isAvailableForBuying (upgradeID))

            renderTradeButton (upgradeID);
        }
    }

  ImGui::End ();
}

void
UIOctopusPanel::renderTradeButton (UpgradeID id) const
{
  auto size = ImVec2 (300.f, 45.f);

  ImGui::BeginDisabled (!upgradeView ()->isBuyable (id));
  std::string buttonText = fmt::format ("{}\n", upgradeView ()->getName (id));

  if (ImGui::Button (buttonText.c_str (), size))
    {
      inputHandler->buy (id);
    }
  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                            | ImGuiHoveredFlags_AllowWhenDisabled)
      && ImGui::BeginTooltip ())
    {
      std::string tooltipText
          = fmt::format ("{}", upgradeView ()->getDescription (id));
      ImGui::Text ("%s", tooltipText.c_str ());

      auto cost = upgradeView ()->getCost (id);
      UIUtils::printCostsImGui (ressourcesView (), cost);

      ImGui::EndTooltip ();
    }

  ImGui::EndDisabled ();
}
