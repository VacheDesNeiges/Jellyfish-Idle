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
UIManager::bindGameData (std::shared_ptr<GameDataSynchronizer> d)
{
  gData = d;
}

void
UIManager::renderUI () const
{
  ImGui::DockSpaceOverViewport (ImGui::GetMainViewport ());

  ImGui::Begin ("Tabs");
  if (ImGui::BeginTabBar ("Tabs", ImGuiTabBarFlags_None))
    {
      renderBuildings ();

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
          ImGui::EndTabItem ();
        }

      ImGui::EndTabBar ();
    }

  ImGui::End ();

  renderRessources ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}

void
UIManager::renderRessources () const
{
  ImGui::Begin ("Ressources");

  ImGui::Text ("Jellyfish");
  ImGui::SameLine ();
  // print the amount of jellies
  std::string jfishtxt = fmt::format ("{}/{}", gData->getNumJellies (),
                                      gData->getMaxNumJellies ());

  auto x = (ImGui::GetCursorPosX () + ImGui::GetColumnWidth ()
            - ImGui::CalcTextSize (jfishtxt.c_str ()).x - ImGui::GetScrollX ()
            - 2 * ImGui::GetStyle ().ItemSpacing.x);
  if (x > ImGui::GetCursorPosX ())
    ImGui::SetCursorPosX (x);
  ImGui::Text ("%s", jfishtxt.c_str ());

  // print each resource name and quantity
  ImGui::Columns (3, nullptr, false);
  ImGui::SetColumnWidth (0, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (1, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (2, ImGui::GetWindowWidth () / 3);
  for (const auto &resource : Ressource::RessourceTypes)
    {
      if (!gData->isUnlocked (resource))
        continue;
      ImGui::SetCursorPosX (ImGui::GetCursorPosX ()
                            + ImGui::GetStyle ().ItemSpacing.x);
      ImGui::Text ("%s", gData->getRessourceName (resource).data ());

      ImGui::SameLine ();
      ImGui::NextColumn ();

      std::ostringstream stream;
      stream << std::fixed;
      stream << std::setprecision (2);
      stream << gData->getRessourceQuantity (resource) << "/"
             << gData->getRessourceMaxQuantity (resource);

      std::string text = stream.str ();
      auto textWidth = ImGui::CalcTextSize (text.c_str ()).x;
      auto columnWidth
          = ImGui::GetColumnWidth () - ImGui::GetStyle ().ItemSpacing.x;
      ImGui::SetCursorPosX (ImGui::GetCursorPosX () + columnWidth - textWidth);
      ImGui::Text ("%s", text.c_str ());

      ImGui::SameLine ();
      ImGui::NextColumn ();

      std::string production = fmt::format (
          "+{}/sec", (gData->getRessourceProduction (resource)
                      - gData->getRessourceConsumption (resource))
                         * 2);
      auto productionWidth = ImGui::CalcTextSize (production.c_str ()).x;
      ImGui::SetCursorPosX (ImGui::GetCursorPosX () + columnWidth
                            - productionWidth - 5);
      ImGui::Text ("%s", production.c_str ());

      ImGui::NextColumn ();
    }
  ImGui::Columns (1);

  ImGui::End ();
}

void
UIManager::renderBuildings () const
{
  if (ImGui::BeginTabItem ("Buildings"))
    {
      ImGui::Text ("This is the Buildings tab!\n wiiiii");
      if (auto sz = ImVec2 (300.f, 20.0f); ImGui::Button ("GatherFood", sz))
        {
          gData->gatherFood ();
        }

      ImGui::SameLine ();
      bool odd = true;

      {
        using enum BuildingType;
        for (const auto &building : Building::BuildingTypes)
          {
            if (renderBuildingButton (building))
              odd = !odd;

            if (odd)
              ImGui::SameLine ();
          }
      }

      ImGui::EndTabItem ();
    }
}

bool
UIManager::renderBuildingButton (BuildingType building) const
{
  auto sz = ImVec2 (300.f, 20.0f);

  if (gData->isUnlocked (building))
    {

      ImGui::BeginDisabled (!gData->isBuyable (building));
      if (ImGui::Button (gData->getBuildingDescription (building).c_str (),
                         sz))
        {
          gData->buy (building);
        }
      ImGui::EndDisabled ();
      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip (
              "%s", gData->getAdvancedBuildingDescription (building).c_str ());
        }

      return true;
    }
  return false;
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
      if (ImGui::Button (
              gData->getAbilityName (AbilityType::CallThunder).c_str ()))
        {
          gData->useAbility (AbilityType::CallThunder);
        }

      if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                | ImGuiHoveredFlags_AllowWhenDisabled))
        {
          ImGui::SetTooltip (
              "%s", gData->getAbilityDescription (AbilityType::CallThunder)
                        .c_str ());
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