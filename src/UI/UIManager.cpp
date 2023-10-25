#include "UIManager.hpp"
#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "imgui.h"
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
      renderJobs ();

      if (ImGui::BeginTabItem ("Territory"))
        {
          ImGui::Text ("This is the Territory tab!\nblah blah blah blah blah");
          ImGui::EndTabItem ();
        }
      if (ImGui::BeginTabItem ("Upgrades"))
        {
          ImGui::Text ("This is the upgrade tab");
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
      if (gData->isUnlocked (AchievementIDs::PlanktonField))
        {

          using enum BuildingType;
          ImGui::BeginDisabled (!gData->isBuyable (PlanktonField));
          if (ImGui::Button (("Plankton Field ("
                              + std::to_string (
                                  gData->getBuildingQuantity (PlanktonField))
                              + ")")
                                 .c_str (),
                             sz))
            {
              gData->buy (PlanktonField);
            }
          ImGui::EndDisabled ();
          if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone
                                    | ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip (
                "%s", gData->getBuildingDescription (PlanktonField).c_str ());
        }

      ImGui::EndTabItem ();
    }
}
void
UIManager::renderJobs () const
{
  if (ImGui::BeginTabItem ("Jobs"))
    {
      using enum JellyJobs;
      ImGui::Text ("Available Jellies : %ld", gData->getNumJellies (None));

      ImGui::Text ("Gather Sand");
      ImGui::SameLine ();
      ImGui::PushButtonRepeat (true);
      if (ImGui::ArrowButton ("##left", ImGuiDir_Left))
        {
          gData->unassignJelly (GatherSand);
        }
      ImGui::SameLine ();
      ImGui::Text ("%ld", gData->getNumJellies (GatherSand));
      ImGui::SameLine (0.0f);
      if (ImGui::ArrowButton ("##right", ImGuiDir_Right))
        {
          gData->assignJelly (GatherSand);
        }
      ImGui::PopButtonRepeat ();

      ImGui::EndTabItem ();
    }
}