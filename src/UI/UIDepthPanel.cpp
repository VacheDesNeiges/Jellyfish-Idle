#include "UIDepthPanel.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIDepthPanel::render () const
{
  if (!ImGui::Begin ("Depth", nullptr,
                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  std::string depthString = fmt::format (
      "Current Depth : {} meters", gData->getDepthView ()->getCurrentDepth ());
  ImGui::Text ("%s", depthString.c_str ());

  ImGui::ProgressBar (
      gData->getDepthView ()->getCurrentProgress ()
      / gData->getDepthView ()->getProgressNeededForNextIncrease ());

  ImGui::Separator ();
  displayDepthsRewards ();

  ImGui::End ();
}

void
UIDepthPanel::displayDepthsRewards () const
{
  const auto &depthRewards = gData->getAchievementsView ()->getDepthRewards ();
  if (depthRewards.empty ())
    return;

  ImGui::SetCursorPosY (100);
  ImGui::SetCursorPosX (50);
  if (ImGui::BeginTable ("Depth Rewards Table", 3,
                         ImGuiTableFlags_RowBg | ImGuiTableFlags_NoHostExtendX
                             | ImGuiTableFlags_SizingFixedFit
                             | ImGuiTableFlags_Borders))
    {
      ImGui::TableSetupScrollFreeze (0, 1);
      ImGui::TableSetupColumn ("Depth");
      ImGui::TableSetupColumn ("Reward");
      ImGui::TableSetupColumn ("Description");
      ImGui::TableHeadersRow ();

      for (const auto &[achievID, depth, name, description] : depthRewards)
        {
          ImGui::TableNextRow ();
          if (gData->getAchievementsView ()->isUnlocked (achievID))
            {
              ImGui::TableSetColumnIndex (0);
              ImGui::Text ("%d", depth);

              ImGui::TableSetColumnIndex (1);
              ImGui::Text ("%s", name.c_str ());

              ImGui::TableSetColumnIndex (2);
              ImGui::Text ("%s", description.c_str ());
            }
        }

      ImGui::EndTable ();
    }
}
