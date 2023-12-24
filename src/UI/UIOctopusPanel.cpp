#include "UIOctopusPanel.hpp"
#include "AchievementDataView.hpp"
#include "InputHandler.hpp"
#include "UpgradeDataView.hpp"
#include "UpgradeId.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIOctopusPanel::render () const
{
  if (!ImGui::Begin ("Octopus", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  for (const auto &upgradeID : Upgrade::upgradeIDs)
    {
      renderTradeButton (upgradeID);
    }

  ImGui::End ();
}

void
UIOctopusPanel::renderTradeButton (UpgradeID id) const
{
  auto size = ImVec2 (300.f, 150.f);
  if (gData->getAchievementsView ()->isUnlocked (id))
    {
      ImGui::BeginDisabled (!gData->getUpgradeView ()->isBuyable (id));
      std::string buttonText
          = fmt::format ("{}\n {}", gData->getUpgradeView ()->getName (id),
                         gData->getUpgradeView ()->getDescription (id));

      if (ImGui::Button (buttonText.c_str (), size))
        {
          inputHandler->buy (id);
        }
      ImGui::EndDisabled ();
    }
}
