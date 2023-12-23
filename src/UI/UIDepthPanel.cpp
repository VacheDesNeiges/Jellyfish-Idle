#include "UIDepthPanel.hpp"
#include "DepthDataView.hpp"
#include "fmt/core.h"
#include "imgui.h"

void
UIDepthPanel::render () const
{
  if (!ImGui::Begin ("Depth"))
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
  ImGui::End ();
}