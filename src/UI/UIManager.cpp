#include "UIManager.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "imgui.h"
#include "imgui_internal.h"
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

      if (ImGui::BeginTabItem ("Insight"))
        {
          ImGui::Text ("Insight Tab");
          ImGui::EndTabItem ();
        }

      if (ImGui::BeginTabItem ("Research"))
        {
          ImGui::Text ("This is the upgrade tab");
          ImGui::EndTabItem ();
        }

      if (gData->isUnlocked (AchievementIDs::JobExploreTheSea))
        {
          if (ImGui::BeginTabItem ("Territory"))
            {
              ImGui::Text (
                  "This is the Territory tab!\nblah blah blah blah blah");
              ImGui::EndTabItem ();
            }
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
  std::string jfishtxt = std::to_string (gData->getNumJellies ()) + "/"
                         + std::to_string (gData->getMaxNumJellies ());

  auto x = (ImGui::GetCursorPosX () + ImGui::GetColumnWidth ()
            - ImGui::CalcTextSize (jfishtxt.c_str ()).x - ImGui::GetScrollX ()
            - 2 * ImGui::GetStyle ().ItemSpacing.x);
  if (x > ImGui::GetCursorPosX ())
    ImGui::SetCursorPosX (x);
  ImGui::Text ("%s", jfishtxt.c_str ());

  for (auto r = static_cast<int> (RessourceType::Food);
       r != static_cast<int> (RessourceType::Last); r++)
    {
      auto ressource = static_cast<RessourceType> (r);
      ImGui::Begin ("Ressources");

      ImGui::Text ("%s", gData->getRessourceName (ressource).data ());
      ImGui::SameLine ();

      ImGui::NextColumn ();

      std::ostringstream stream;
      stream << std::fixed;
      stream << std::setprecision (2);
      stream << gData->getRessourceQuantity (ressource) << "/"
             << gData->getRessourceMaxQuantity (ressource);

      std::string text = stream.str ();

      auto posX
          = (ImGui::GetCursorPosX () + ImGui::GetColumnWidth ()
             - ImGui::CalcTextSize (text.c_str ()).x - ImGui::GetScrollX ()
             - 2 * ImGui::GetStyle ().ItemSpacing.x);
      if (posX > ImGui::GetCursorPosX ())
        ImGui::SetCursorPosX (posX);
      ImGui::Text ("%s", text.c_str ());

      ImGui::End ();
    }
  ImGui::End ();
}

void
UIManager::renderBuildings () const
{
  if (ImGui::BeginTabItem ("Buildings"))
    {
      ImGui::Text ("This is the Buildings tab!\n wiiiii");
      auto sz = ImVec2 (300.f, 20.0f);
      if (ImGui::Button ("GatherFood", sz))
        {
          gData->gatherFood ();
        }

      ImGui::SameLine ();
      bool odd = true;

      {
        using enum BuildingType;
        for (auto building = static_cast<int> (PlanktonField);
             building != static_cast<int> (Last); building++)
          {
            if (renderBuildingButton (static_cast<BuildingType> (building)))
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