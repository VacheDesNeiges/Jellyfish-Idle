#include "UIJobsPanel.hpp"
#include "Jellyfish.hpp"
#include "imgui.h"

void
UIJobsPanel::render () const
{
  if (ImGui::BeginTabItem ("Jobs"))
    {
      using enum JellyJobs;

      ImGui::Text ("Available Jellies : %ld", gData->getNumJellies (None));

      for (auto job = static_cast<int> (GatherSand);
           job != static_cast<int> (Last); job++)
        {
          if (gData->isUnlocked (static_cast<JellyJobs> (job)))
            renderJobsControls (static_cast<JellyJobs> (job));
        }

      ImGui::EndTabItem ();
    }
}

void
UIJobsPanel::renderJobsControls (JellyJobs job) const
{
  ImGui::Text ("%s", gData->getJobDescription (job).c_str ());
  ImGui::SameLine ();
  ImGui::PushButtonRepeat (true);
  auto s = gData->getJobDescription (job);
  if (ImGui::ArrowButton ((s + "##left").c_str (), ImGuiDir_Left))
    {
      gData->unassignJelly (job);
    }
  ImGui::SameLine ();
  ImGui::Text ("%ld", gData->getNumJellies (job));
  ImGui::SameLine (0.0f);
  if (ImGui::ArrowButton ((s + "##right").c_str (), ImGuiDir_Right))
    {
      gData->assignJelly (job);
    }
  ImGui::PopButtonRepeat ();
}