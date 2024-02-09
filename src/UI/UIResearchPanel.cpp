#include "UIResearchPanel.hpp"
#include "imgui.h"

void
UIResearchPanel::render () const
{
  if (!ImGui::Begin ("Research", nullptr, ImGuiWindowFlags_None))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("This is the upgrade tab");
  ImGui::End ();
}