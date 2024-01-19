#include "UIJobsPanel.hpp"
#include "CraftingDataView.hpp"
#include "CraftingRecipe.hpp"
#include "GameDataView.hpp"
#include "InputHandler.hpp"
#include "Jellyfish.hpp"
#include "RecipeID.hpp"
#include "UIUtils.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <fmt/core.h>

void
UIJobsPanel::render () const
{
  if (!ImGui::Begin ("Jobs", nullptr, ImGuiWindowFlags_NoMove))
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

  ImGui::SeparatorText ("Recipes");

  renderRecipes ();

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

  ImGui::Text ("%s", recipeName.c_str ());

  const std::string quantity = fmt::format (
      "{:.2f}", gData->getCraftView ()->getCraftResults (id)[0].second);

  ImGui::SameLine (ImGui::GetWindowWidth ()
                   - (ImGui::CalcTextSize (quantity.c_str ()).x + 10));
  ImGui::Text ("%s", quantity.c_str ());

  ImGui::SeparatorText ("Assigned Artisans");
  if (ImGui::ArrowButton ((recipeName + "##left").c_str (), ImGuiDir_Left))
    {
      inputHandler->unassignToRecipe (id);
    }
  ImGui::SameLine ();
  ImGui::Text ("%d", gData->getCraftView ()->getAssignedNumOfJellies (id));
  ImGui::SameLine ();
  if (ImGui::ArrowButton ((recipeName + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignToRecipe (id);
    }

  ImGui::SeparatorText ("Recipe");
  displayRecipeText (id);
  ImGui::Separator ();

  if (ImGui::Button ("Start"))
    {
      inputHandler->startRecipe (id);
    }
  ImGui::SameLine ();
  if (ImGui::Button ("cancel"))
    {
      inputHandler->cancelRecipe (id);
    }
  ImGui::ProgressBar (
      1
      - static_cast<float> (gData->getCraftView ()->getRemainingTicks (id))
            / static_cast<float> (
                gData->getCraftView ()->getTotalRequiredTicks (id)));

  ImGui::EndChild ();
}

void
UIJobsPanel::displayRecipeText (RecipeID id) const
{
  const auto &craftRecipe = gData->getCraftView ()->getRecipe (id);
  std::string craftResultString;

  UIUtils::printCostsImGui (gData, craftRecipe);
}