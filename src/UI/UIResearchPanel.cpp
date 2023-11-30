#include "UIResearchPanel.hpp"
#include "imgui.h"

void
UIResearchPanel::render () const
{
  if (ImGui::BeginTabItem ("Research"))
    {
      ImGui::Text ("This is the upgrade tab");
      ImGui::EndTabItem ();
    }
}