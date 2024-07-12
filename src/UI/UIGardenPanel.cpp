#include "UIGardenPanel.hpp"
#include "GameIDsTypes.hpp"
#include "UIUtils.hpp"
#include "imgui.h"
#include <fmt/core.h>
#include <string>

void
UIGardenPanel::render () const
{
  if (!ImGui::Begin ("Garden", nullptr,

                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("Avaiables fields : %d",
               gData->getGardenView ()->getAssignedFieldsToCulture (
                   CulturesAlias::NONE));

  ImGui::PushStyleColor (ImGuiCol_ChildBg, IM_COL32 (0, 0, 0, 220));
  ImGui::PushStyleColor (ImGuiCol_Separator,
                         ImVec4 (0.791f, 0.130f, 0.130f, 0.652f));
  for (const auto &culture : gData->getGardenView ()->getCultureTypes ())
    {
      if (gData->getAchievementsView ()->isUnlocked (culture))
        {
          renderCulture (culture);
          ImGui::SameLine ();
        }
    }
  ImGui::PopStyleColor (2);
  ImGui::End ();
}

void
UIGardenPanel::renderCulture (AquaCultureID id) const
{
  constexpr auto size = ImVec2 (200, 270);
  const auto &cultureName = gData->getGardenView ()->getName (id);

  ImGui::BeginChild (cultureName.c_str (), size);

  ImGui::SeparatorText (cultureName.c_str ());
  displayCultureProduction (id);

  ImGui::SeparatorText ("Assigned Fields ");
  displayFieldsAssignmentArrows (cultureName, id);
  displayGrowAndStopButtons (id);

  ImGui::SeparatorText ("Cost");
  displayCultureCost (id);

  ImGui::EndChild ();
}

void
UIGardenPanel::displayCultureProduction (AquaCultureID id) const
{
  ImGui::Text ("Each field produces :");
  ImGui::NewLine ();

  const auto [rType, quant]
      = gData->getGardenView ()->getFieldProduction (id, 1).at (0);

  const std::string quantity = fmt::format (
      "{} x {:.3f}/sec", gData->getRessourcesView ()->getRessourceName (rType),
      quant * 2);

  ImGui::Text ("%s", quantity.c_str ());
}

void
UIGardenPanel::displayFieldsAssignmentArrows (const std::string &cultureName,
                                              AquaCultureID id) const
{
  ImGui::BeginDisabled (
      gData->getGardenView ()->isOngoing (id)
      || (gData->getGardenView ()->getAssignedFieldsToCulture (id) == 0));

  ImGui::SetCursorPosX (ImGui::GetCursorPosX () + 67);

  if (ImGui::ArrowButton ((cultureName + "##left").c_str (), ImGuiDir_Left))
    {
      inputHandler->unassignToField (id);
    }

  ImGui::EndDisabled ();

  ImGui::SameLine ();

  ImGui::Text ("%d", gData->getGardenView ()->getAssignedFieldsToCulture (id));

  ImGui::SameLine ();

  ImGui::BeginDisabled (
      gData->getGardenView ()->isOngoing (id)
      || gData->getGardenView ()->getAssignedFieldsToCulture (
             CulturesAlias::NONE)
             == 0);
  if (ImGui::ArrowButton ((cultureName + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignToField (id);
    }
  ImGui::EndDisabled ();
}

void
UIGardenPanel::displayCultureCost (
    AquaCultureID id) const // TODO write garden own function instead of
                            // reusing the one from crafting
{
  const auto &costData = gData->getGardenView ()->getFieldConsumption (id);
  if (costData.empty ())
    {
      ImGui::Text ("Nothing");
    }
  else
    {
      UIUtils::printCostsImGui (gData, costData);
    }
}

void
UIGardenPanel::displayGrowAndStopButtons (AquaCultureID id) const
{
  ImGui::BeginDisabled (
      gData->getGardenView ()->getAssignedFieldsToCulture (id) == 0
      || (gData->getGardenView ()->isOngoing (id)));

  ImGui::SetCursorPosX (ImGui::GetCursorPosX () + 25);

  if (ImGui::Button ("Grow"))
    {
      inputHandler->startCulture (id);
    }
  ImGui::EndDisabled ();

  ImGui::SameLine ();

  ImGui::BeginDisabled (!gData->getGardenView ()->isOngoing (id));
  if (ImGui::Button ("Stop"))
    {
      inputHandler->cancelCulture (id);
    }
  ImGui::EndDisabled ();
}
