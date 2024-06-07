#include "UIResearchPanel.hpp"
#include "imgui.h"

void
UIResearchPanel::render () const
{
  if (!ImGui::Begin ("Research", nullptr,
                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("This is the upgrade tab");
  ImGui::End ();
}