#include "UIRessourcesPanel.hpp"

#include "GameIDsTypes.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include "imgui_internal.h"

#include <cfloat>
#include <iomanip>

void
UIRessourcesPanel::render () const
{
  renderRessources ();
  if (gData->getAchievementsView ()->isUnlocked (
          AchievementsAlias::ANYMANUFACTUREDRESSOURCE))
    renderManufacturedRessources ();
}

void
UIRessourcesPanel::renderRessources () const
{
  if (!ImGui::Begin ("Ressources", nullptr, ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  ImGui::Text ("Jellyfish");
  ImGui::SameLine ();
  // print the amount of jellies
  std::string jfishtxt
      = fmt::format ("{}/{}", gData->getJelliesView ()->getNumJellies (),
                     gData->getJelliesView ()->getMaxNumJellies ());

  auto x = (ImGui::GetCursorPosX () + ImGui::GetColumnWidth ()
            - ImGui::CalcTextSize (jfishtxt.c_str ()).x - ImGui::GetScrollX ()
            - 2 * ImGui::GetStyle ().ItemSpacing.x);

  if (x > ImGui::GetCursorPosX ())
    ImGui::SetCursorPosX (x);

  ImGui::Text ("%s", jfishtxt.c_str ());

  ImGui::SeparatorText ("");

  setupColumns ();
  for (const auto &ressource :
       gData->getRessourcesView ()->getRegularRessourceTypes ())
    {
      if (!gData->getAchievementsView ()->isUnlocked (ressource))
        continue;
      renderRessource (ressource);
    }
  ImGui::EndColumns ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementsAlias::ANYRARERESSOURCE))
    {
      ImGui::SeparatorText ("Rare Ressources");
      setupColumns ();
      for (const auto &rareRessource :
           gData->getRessourcesView ()->getRareRessourceTypes ())
        {
          if (!gData->getAchievementsView ()->isUnlocked (rareRessource))
            continue;
          renderRessource (rareRessource);
        }
      ImGui::EndColumns ();
    }

  ImGui::End ();
}

void
UIRessourcesPanel::renderManufacturedRessources () const
{
  if (!ImGui::Begin ("Manufactured Ressources", nullptr,
                     ImGuiWindowFlags_NoMove))
    {
      ImGui::End ();
      return;
    }

  setupColumns ();
  for (const auto &ressource :
       gData->getRessourcesView ()->getCraftableRessourceTypes ())
    {
      if (!gData->getAchievementsView ()->isUnlocked (ressource))
        continue;
      renderRessource (ressource);
    }
  ImGui::EndColumns ();

  ImGui::End ();
}

void
UIRessourcesPanel::renderRessource (RessourceType ressource) const
{
  ImGui::SetCursorPosX (ImGui::GetCursorPosX ()
                        + ImGui::GetStyle ().ItemSpacing.x);
  ImGui::Text (
      "%s", gData->getRessourcesView ()->getRessourceName (ressource).data ());

  ImGui::SameLine ();
  ImGui::NextColumn ();

  std::ostringstream stream;
  stream << std::fixed;
  stream << std::setprecision (3);
  stream << gData->getRessourcesView ()->getRessourceQuantity (ressource);

  if (!(gData->getRessourcesView ()->getRessourceMaxQuantity (ressource)
        == DBL_MAX)
      && !(gData->getRessourcesView ()->getRessourceMaxQuantity (ressource)
           == -1))
    {
      stream << " /"
             << gData->getRessourcesView ()->getRessourceMaxQuantity (
                    ressource);
    }

  std::string text = stream.str ();
  auto textWidth = ImGui::CalcTextSize (text.c_str ()).x;
  auto columnWidth
      = ImGui::GetColumnWidth () - ImGui::GetStyle ().ItemSpacing.x;
  ImGui::SetCursorPosX (ImGui::GetCursorPosX () + columnWidth - textWidth);
  ImGui::Text ("%s", text.c_str ());

  ImGui::SameLine ();
  ImGui::NextColumn ();

  std::string production = fmt::format (
      "{:.3f}/sec",
      (gData->getRessourcesView ()->getRessourceProduction (ressource)
       - gData->getRessourcesView ()->getRessourceConsumption (ressource))
          * 2);
  auto productionWidth = ImGui::CalcTextSize (production.c_str ()).x;
  ImGui::SetCursorPosX (ImGui::GetCursorPosX () + columnWidth - productionWidth
                        - 5);
  ImGui::Text ("%s", production.c_str ());

  ImGui::NextColumn ();
}

void
UIRessourcesPanel::setupColumns () const
{
  ImGui::Columns (3, nullptr, false);
  ImGui::SetColumnWidth (0, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (1, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (2, ImGui::GetWindowWidth () / 3);
}