#include "UIJobsPanel.hpp"

#include "GameIDsTypes.hpp"
#include "UIUtils.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include "imgui_internal.h"

#include <string>

void
UIJobsPanel::render () const
{
  if (!ImGui::Begin ("Jobs", nullptr,
                     ImGuiWindowFlags_NoMove
                         & ImGuiWindowFlags_NoFocusOnAppearing))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("Available Jellies : %d",
               gData->getJelliesView ()->getNumJellies (JobsAlias::NONE));

  renderJobsControls ();

  if (gData->getUpgradeView ()->isBought (UpgradesAlias::ADVANCEDTELEKINESIS))
    {
      ImGui::SeparatorText ("Recipes");

      renderRecipes ();
    }
  ImGui::End ();
}

void
UIJobsPanel::renderJobsControls () const
{
  ImGui::Columns (3, nullptr, false);
  const auto columnWidth = ImGui::GetWindowWidth () / 6;
  ImGui::SetColumnWidth (0, columnWidth);
  ImGui::SetColumnWidth (1, columnWidth);
  ImGui::SetColumnWidth (2, columnWidth);

  for (const auto job : gData->getJelliesView ()->getAllJobsTypes ())
    {
      if (gData->getAchievementsView ()->isUnlocked (job))
        {
          ImGui::Text (
              "%s",
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

          if (gData->getAchievementsView ()->isUnlocked (
                  UpgradesAlias::LEVELING))
            {
              ImGui::SameLine ();
              ImGui::Text ("lvl %u",
                           gData->getJelliesView ()->getJobLevel (job));
            }
          ImGui::NextColumn ();

          if (gData->getAchievementsView ()->isUnlocked (
                  UpgradesAlias::LEVELING))
            {
              auto lvlProgress
                  = gData->getJelliesView ()->getCurrentProgress (job)
                    / gData->getJelliesView ()->getProgressNeeded (job);
              ImGui::ProgressBar (static_cast<float> (lvlProgress));
            }

          ImGui::NextColumn ();
        }
    }
  ImGui::EndColumns ();
}

void
UIJobsPanel::renderRecipes () const
{
  ImGui::Text ("%s",
               fmt::format ("Available Artisans : {}",
                            gData->getCraftView ()->getAssignedNumOfJellies (
                                RecipesAlias::NONE))
                   .c_str ());

  ImGui::PushStyleColor (ImGuiCol_ChildBg, UIColors::CardElements);
  ImGui::PushStyleColor (ImGuiCol_Separator,
                         ImVec4 (0.791f, 0.130f, 0.130f, 0.652f));
  for (const auto &recipe : gData->getCraftView ()->getRecipeTypes ())
    {
      renderRecipe (recipe);
      ImGui::SameLine ();
    }
  ImGui::PopStyleColor (2);
}

void
UIJobsPanel::renderRecipe (RecipeID id) const
{
  constexpr auto size = ImVec2 (200, 260);
  const auto &recipeName = gData->getCraftView ()->getName (id);

  ImGui::BeginChild (recipeName.c_str (), size);

  ImGui::SeparatorText (recipeName.c_str ());

  ImGui::Text ("Produces :");

  const std::string quantity
      = fmt::format ("{} x {:.3f}", recipeName,
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

  ImGui::BeginDisabled (
      gData->getCraftView ()->craftIsOngoing (id)
      || (gData->getCraftView ()->getAssignedNumOfJellies (RecipesAlias::NONE)
          == 0));
  if (ImGui::ArrowButton ((recipeName + "##right").c_str (), ImGuiDir_Right))
    {
      inputHandler->assignToRecipe (id);
    }
  ImGui::EndDisabled ();

  ImGui::SeparatorText ("Recipe");
  displayRecipeText (id);
  ImGui::SeparatorText ("");

  ImGui::BeginDisabled (gData->getCraftView ()->getAssignedNumOfJellies (id)
                            == 0
                        || (!gData->getCraftView ()->canAfford (id))
                        || gData->getCraftView ()->craftIsOngoing (id));
  if (ImGui::Button ("Start", { 0, 30.f }))
    {
      inputHandler->startRecipe (id);
    }
  ImGui::EndDisabled ();
  ImGui::SameLine ();
  ImGui::BeginDisabled (!gData->getCraftView ()->craftIsOngoing (id));

  if (ImGui::Button ("Cancel", { 0, 30.f }))
    {
      inputHandler->cancelRecipe (id);
    }
  ImGui::EndDisabled ();
  ImGui::SameLine ();
  renderLoopButton (id);

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

void
UIJobsPanel::renderLoopButton (RecipeID id) const
{
  ImVec2 size{ 24.f, 24.f };
  ImVec2 uv0{ 0.0f, 0.0f };
  ImVec2 uv1{ 1.0f, 1.0f };
  auto bgColor = UIColors::Buttons;

  ImVec4 tintColor;

  bool isEnabled = gData->getCraftView ()->isKeepCraftingEnabled (id);
  if (isEnabled)
    {
      tintColor = UIColors::ActivatedElement;
    }
  else
    {
      tintColor = UIColors::CardElements;
    }

  ImGui::PushStyleVar (ImGuiStyleVar_FramePadding, { 3, 3 });
  ImGui::PushStyleColor (ImGuiCol_ButtonActive,
                         ImGui::GetStyle ().Colors[ImGuiCol_Button]);
  ImGui::PushStyleColor (ImGuiCol_ButtonHovered,
                         ImGui::GetStyle ().Colors[ImGuiCol_Button]);

  ImGui::BeginDisabled (gData->getCraftView ()->getAssignedNumOfJellies (id)
                        == 0);

  if (ImGui::ImageButton ("##", loopButtonTexture, size, uv0, uv1, bgColor,
                          tintColor))
    {
      inputHandler->setKeepCraftingMode (id, !isEnabled);
    }
  if (ImGui::IsItemHovered (ImGuiHoveredFlags_DelayNone)
      && ImGui::BeginTooltip ())
    {
      ImGui::SetTooltip ("Auto-Start when ressources are available");
      ImGui::EndTooltip ();
    }
  ImGui::EndDisabled ();
  ImGui::PopStyleVar ();
  ImGui::PopStyleColor (2);
}