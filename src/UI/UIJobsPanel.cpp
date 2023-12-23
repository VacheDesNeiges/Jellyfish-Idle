#include "UIJobsPanel.hpp"
#include "AchievementDataView.hpp"
#include "InputHandler.hpp"
#include "Jellyfish.hpp"
#include "JellyfishDataView.hpp"
#include "imgui.h"

void
UIJobsPanel::render () const
{
  if (!ImGui::Begin ("Jobs"))
    {
      ImGui::End ();
      return;
    }

  using enum JellyJobs;

  ImGui::Text ("Available Jellies : %ld",
               gData->getJelliesView ()->getNumJellies (None));

  for (auto job = static_cast<int> (GatherSand);
       job != static_cast<int> (Last); job++)
    {
      if (gData->getAchievementsView ()->isUnlocked (
              static_cast<JellyJobs> (job)))
        renderJobsControls (static_cast<JellyJobs> (job));
    }

  ImGui::End ();
}

void
UIJobsPanel::renderJobsControls (JellyJobs job) const
{
  ImGui::Text ("%s",
               gData->getJelliesView ()->getJobDescription (job).c_str ());
  ImGui::SameLine ();
  ImGui::PushButtonRepeat (true);
  auto s = gData->getJelliesView ()->getJobDescription (job);
  if (ImGui::ArrowButton ((s + "##left").c_str (), ImGuiDir_Left))
    {
      inputHandler->unassignJelly (job);
    }
  ImGui::SameLine ();
  ImGui::Text ("%ld", gData->getJelliesView ()->getNumJellies (job));
  ImGui::SameLine (0.0f);
  if (ImGui::ArrowButton ((s + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignJelly (job);
    }
  ImGui::PopButtonRepeat ();
}