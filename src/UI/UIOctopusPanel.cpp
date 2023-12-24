#include "UIOctopusPanel.hpp"
#include "imgui.h"

void
UIOctopusPanel::render () const
{
  if (!ImGui::Begin ("Octopus", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  ImGui::End ();
}