#include "UIResearchPanel.hpp"
#include "imgui.h"

void
UIResearchPanel::render () const
{
  if (!ImGui::Begin ("Research"))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("This is the upgrade tab");
  ImGui::End ();
}