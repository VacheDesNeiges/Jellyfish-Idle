#include "UIGardenPanel.hpp"
#include "AquaCulture.hpp"
#include "imgui.h"

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

  ImGui::SeparatorText ("Assigned Fields ");

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

  ImGui::EndChild ();
}