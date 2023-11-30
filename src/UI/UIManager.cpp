#include "UIManager.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <fmt/core.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

void
UIManager::bindGameData (std::shared_ptr<GameDataSynchronizer> ptr)
{
  gData = ptr;
  ressourcesPanel.bindGameData (ptr);
  buildingsPanel.bindGameData (ptr);
}

void
UIManager::renderUI () const
{
  ImGui::DockSpaceOverViewport (ImGui::GetMainViewport ());

  ImGui::Begin ("Tabs");
  if (ImGui::BeginTabBar ("Tabs", ImGuiTabBarFlags_None))
    {
      buildingsPanel.render ();

      if (gData->isUnlocked (AchievementIDs::FirstJelly))
        renderJobs ();

      if (gData->isUnlocked (AchievementIDs::FirstInsightAbility))
        {
          renderInsightAbilities ();
        }

      if (gData->isUnlocked (AchievementIDs::ResearchTabUnlocked))
        {
          renderResearch ();
        }

      if (gData->isUnlocked (AchievementIDs::JobExploreTheDepths)
          && ImGui::BeginTabItem ("Depths"))
        {
          ImGui::Text ("Wiiiiii");
          std::string depthString
              = fmt::format ("Current Depth : {}", gData->getCurrentDepth ());
          ImGui::Text ("%s", depthString.c_str ());
          ImGui::ProgressBar (gData->getDepthProgress ());
          ImGui::EndTabItem ();
        }

      ImGui::EndTabBar ();
    }

  ImGui::End ();

  ressourcesPanel.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}

void
UIManager::renderJobs () const
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
UIManager::renderJobsControls (JellyJobs job) const
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

void
UIManager::renderInsightAbilities () const
{
  if (ImGui::BeginTabItem ("Insight"))
    {
      using enum AbilityType;
      if (ImGui::Button (gData->getAbilityName (CallThunder).c_str ()))
        {
          gData->useAbility (CallThunder);
        }

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip (
              "%s", gData->getAbilityDescription (CallThunder).c_str ());
        }

      ImGui::Text ("Insight Tab");
      ImGui::EndTabItem ();
    }
}

void
UIManager::renderResearch () const
{
  if (ImGui::BeginTabItem ("Research"))
    {
      ImGui::Text ("This is the upgrade tab");
      ImGui::EndTabItem ();
    }
}