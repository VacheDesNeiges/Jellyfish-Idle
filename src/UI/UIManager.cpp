#include "UIManager.hpp"
#include "Building.hpp"
#include "Ressource.hpp"
#include "imgui.h"
#include <iomanip>
#include <ios>
#include <iostream>
#include <src/GameData/GameDataSynchronizer.hpp>
#include <src/Jellyfishs/Jellyfish.hpp>
#include <sstream>
#include <string>

void
UIManager::renderRessources () const
{
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
}

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
      if (ImGui::BeginTabItem ("Buildings"))
        {
          ImGui::Text ("This is the Buildings tab!\n wiiiii");
          auto sz = ImVec2 (300.f, 20.0f);
          if (ImGui::Button ("GatherFood", sz))
            {
              gData->gatherFood ();
            }
          ImGui::SameLine ();
          if (ImGui::Button (("Plankton Field ("
                              + std::to_string (gData->getBuildingQuantity (
                                  BuildingType::PlanktonField))
                              + ")")
                                 .c_str (),
                             sz))
            {
              gData->buy (BuildingType::PlanktonField);
            }

          ImGui::EndTabItem ();
        }
      if (ImGui::BeginTabItem ("Jobs"))
        {
          ImGui::Text ("Available Jellies : %ld",
                       gData->getNumJellies (JellyJobs::None));

          ImGui::Text ("Gather Sea Shells");
          ImGui::SameLine ();
          ImGui::PushButtonRepeat (true);
          if (ImGui::ArrowButton ("##left", ImGuiDir_Left))
            {
              gData->unassignJelly (JellyJobs::GatherSeaShell);
            }
          ImGui::SameLine ();
          ImGui::Text ("%ld",
                       gData->getNumJellies (JellyJobs::GatherSeaShell));
          ImGui::SameLine (0.0f);
          if (ImGui::ArrowButton ("##right", ImGuiDir_Right))
            {
              gData->assignJelly (JellyJobs::GatherSeaShell);
            }
          ImGui::PopButtonRepeat ();

          ImGui::EndTabItem ();
        }
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
  //   ImGui::ShowStyleEditor ();
}