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

  ImGui::EndChild ();
}