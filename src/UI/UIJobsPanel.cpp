#include "UIJobsPanel.hpp"
#include "CraftingDataView.hpp"
#include "CraftingRecipe.hpp"
#include "InputHandler.hpp"
#include "Jellyfish.hpp"
#include "RecipeID.hpp"
#include "UIUtils.hpp"
#include "UpgradeId.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <string>

void
UIJobsPanel::render () const
{
  if (!ImGui::Begin ("Jobs", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  using enum JellyJobs;

  ImGui::Text ("Available Jellies : %d",
               gData->getJelliesView ()->getNumJellies (None));

  for (const auto job : Jellyfish::JobsTypes)
    {
      if (gData->getAchievementsView ()->isUnlocked (job))
        renderJobsControls (job);
    }
  ImGui::EndColumns (); // TODO handle columns of renderjobcontrols() more
                        // cleanly

  if (gData->getUpgradeView ()->isBought (UpgradeID::AdvancedTelekinesis))
    {
      ImGui::SeparatorText ("Recipes");

      renderRecipes ();
    }
  ImGui::End ();
}

void
UIJobsPanel::renderJobsControls (JellyJobs job) const
{
  ImGui::Columns (3, nullptr, false);
  ImGui::SetColumnWidth (0, ImGui::GetWindowWidth () / 6);
  ImGui::SetColumnWidth (1, ImGui::GetWindowWidth () / 6);
  ImGui::SetColumnWidth (2, ImGui::GetWindowWidth () / 6);

  ImGui::Text ("%s",
               gData->getJelliesView ()->getJobDescription (job).c_str ());
  ImGui::SameLine ();
  ImGui::NextColumn ();

  ImGui::PushButtonRepeat (true);
  auto s = gData->getJelliesView ()->getJobDescription (job);
  if (ImGui::ArrowButton ((s + "##left").c_str (), ImGuiDir_Left))
    {
      inputHandler->unassignJelly (job);
    }
  ImGui::SameLine ();
  ImGui::Text ("%d", gData->getJelliesView ()->getNumJellies (job));
  ImGui::SameLine (0.0f);
  if (ImGui::ArrowButton ((s + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignJelly (job);
    }
  ImGui::PopButtonRepeat ();

  ImGui::SameLine ();
  ImGui::Text ("lvl %u", gData->getJelliesView ()->getJobLevel (job));
  ImGui::SameLine ();
  ImGui::NextColumn ();

  auto lvlProgress = gData->getJelliesView ()->getCurrentProgress (job)
                     / gData->getJelliesView ()->getProgressNeeded (job);
  ImGui::ProgressBar (static_cast<float> (lvlProgress));
  ImGui::NextColumn ();
}

void
UIJobsPanel::renderRecipes () const
{
  ImGui::Text ("%s",
               fmt::format ("Available Artisans : {}",
                            gData->getCraftView ()->getAssignedNumOfJellies (
                                RecipeID::NoneRecipe))
                   .c_str ());

  ImGui::PushStyleColor (ImGuiCol_ChildBg, IM_COL32 (0, 0, 0, 180));
  for (const auto &recipe : CraftingRecipe::RecipeTypes)
    {
      renderRecipe (recipe);
      ImGui::SameLine ();
    }
  ImGui::PopStyleColor ();
}

void
UIJobsPanel::renderRecipe (RecipeID id) const
{
  constexpr auto size = ImVec2 (200, 300);
  const auto &recipeName = gData->getCraftView ()->getName (id);

  ImGui::BeginChild (recipeName.c_str (), size);

  ImGui::SeparatorText (recipeName.c_str ());

  ImGui::Text ("Produces :");

  const std::string quantity
      = fmt::format ("{} x {:.2f}", recipeName,
                     gData->getCraftView ()->getCraftResults (id)[0].second);

  ImGui::SameLine (ImGui::GetWindowWidth ()
                   - (ImGui::CalcTextSize (quantity.c_str ()).x + 10));
  ImGui::Text ("%s", quantity.c_str ());

  ImGui::SeparatorText ("Assigned Artisans");

  ImGui::BeginDisabled (
      gData->getCraftView ()->craftIsOngoing (id)
      || (gData->getCraftView ()->getAssignedNumOfJellies (id) == 0));
  if (ImGui::ArrowButton ((recipeName + "##left").c_str (), ImGuiDir_Left))
    {
      inputHandler->unassignToRecipe (id);
    }
  ImGui::EndDisabled ();

  ImGui::SameLine ();
  ImGui::Text ("%d", gData->getCraftView ()->getAssignedNumOfJellies (id));
  ImGui::SameLine ();

  ImGui::BeginDisabled (gData->getCraftView ()->craftIsOngoing (id)
                        || (gData->getCraftView ()->getAssignedNumOfJellies (
                                RecipeID::NoneRecipe)
                            == 0));
  if (ImGui::ArrowButton ((recipeName + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignToRecipe (id);
    }
  ImGui::EndDisabled ();

  ImGui::SeparatorText ("Recipe");
  displayRecipeText (id);
  ImGui::Separator ();

  ImGui::BeginDisabled (gData->getCraftView ()->getAssignedNumOfJellies (id)
                            == 0
                        || (!gData->getCraftView ()->canAfford (id))
                        || gData->getCraftView ()->craftIsOngoing (id));
  if (ImGui::Button ("Start"))
    {
      inputHandler->startRecipe (id);
    }
  ImGui::EndDisabled ();
  ImGui::SameLine ();
  ImGui::BeginDisabled (!gData->getCraftView ()->craftIsOngoing (id));

  if (ImGui::Button ("cancel"))
    {
      inputHandler->cancelRecipe (id);
    }
  ImGui::EndDisabled ();

  const auto progress
      = 1.f
        - (static_cast<float> (gData->getCraftView ()->getRemainingTicks (id))
           / static_cast<float> (
               gData->getCraftView ()->getTotalRequiredTicks (id)));

  const auto &remainingTime = fmt::format (
      "{} seconds", gData->getCraftView ()->getRemainingTicks (id) / 2);

  ImGui::ProgressBar (progress, ImVec2 (-1.0f, 0.0f), remainingTime.c_str ());

  ImGui::EndChild ();
}

void
UIJobsPanel::displayRecipeText (RecipeID id) const
{
  const auto &craftRecipe = gData->getCraftView ()->getRecipe (id);
  std::string craftResultString;

  UIUtils::printCostsImGui (gData, craftRecipe);
}