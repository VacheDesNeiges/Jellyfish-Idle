#include "UIGardenPanel.hpp"
#include "AquaCulture.hpp"
#include "GardenDataView.hpp"
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
                   AquaCultureID::None));

  ImGui::PushStyleColor (ImGuiCol_ChildBg, IM_COL32 (0, 0, 0, 180));
  for (const auto &culture : AquaCulture::CultureTypes)
    {
      renderCulture (culture);
      ImGui::SameLine ();
    }
  ImGui::PopStyleColor ();
  ImGui::End ();
}

void
UIGardenPanel::renderCulture (AquaCultureID id) const
{
  constexpr auto size = ImVec2 (200, 300);
  const auto &cultureName = gData->getGardenView ()->getName (id);

  ImGui::BeginChild (cultureName.c_str (), size);

  ImGui::SeparatorText (cultureName.c_str ());
  displayCultureProduction (cultureName, id);

  ImGui::SeparatorText ("Assigned Fields ");
  displayFieldsAssignmentArrows (cultureName, id);

  ImGui::SeparatorText ("Cost");
  displayCultureCost (id);

  ImGui::SeparatorText ("");
  displayStartAndCancelButtons (id);
  displayProgressBar (id);

  ImGui::EndChild ();
}

void
UIGardenPanel::displayCultureProduction (const std::string &cultureName,
                                         AquaCultureID id) const
{
  ImGui::Text ("Produces :");
  const std::string quantity
      = fmt::format ("{} x {:.2f}", cultureName,
                     gData->getGardenView ()->getFieldResults (id)[0].second);
  ImGui::SameLine (ImGui::GetWindowWidth ()
                   - (ImGui::CalcTextSize (quantity.c_str ()).x + 10));
  ImGui::Text ("%s", quantity.c_str ());
}

void
UIGardenPanel::displayFieldsAssignmentArrows (const std::string &cultureName,
                                              AquaCultureID id) const
{
  ImGui::BeginDisabled (
      gData->getGardenView ()->isOngoing (id)
      || (gData->getGardenView ()->getAssignedFieldsToCulture (id) == 0));
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
             AquaCultureID::None)
             == 0);
  if (ImGui::ArrowButton ((cultureName + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignToField (id);
    }
  ImGui::EndDisabled ();
}

void
UIGardenPanel::displayCultureCost (AquaCultureID id) const
{
  const auto &costData = gData->getGardenView ()->getFieldCost (id);
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
UIGardenPanel::displayStartAndCancelButtons (AquaCultureID id) const
{
  ImGui::BeginDisabled (
      gData->getGardenView ()->getAssignedFieldsToCulture (id) == 0
      || (gData->getGardenView ()->isOngoing (id))
      || (!gData->getGardenView ()->canAfford (id)));

  if (ImGui::Button ("Start"))
    {
      inputHandler->startCulture (id);
    }
  ImGui::EndDisabled ();

  ImGui::SameLine ();

  ImGui::BeginDisabled (!gData->getGardenView ()->isOngoing (id));
  if (ImGui::Button ("Cancel"))
    {
      inputHandler->cancelCulture (id);
    }
  ImGui::EndDisabled ();
}

void
UIGardenPanel::displayProgressBar (AquaCultureID id) const
{
  const auto progress
      = 1.f
        - (static_cast<float> (gData->getGardenView ()->getRemainingTicks (id))
           / static_cast<float> (
               gData->getGardenView ()->getTotalRequiredTicks (id)));

  const auto &remainingTime = fmt::format (
      "{} seconds", gData->getGardenView ()->getRemainingTicks (id) / 2);

  ImGui::ProgressBar (progress, ImVec2 (-1.0f, 0.0f), remainingTime.c_str ());
}