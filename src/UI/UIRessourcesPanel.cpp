#include "UIRessourcesPanel.hpp"
#include "AchievementDataView.hpp"
#include "JellyfishDataView.hpp"
#include "RessourceDataView.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include <iomanip>

void
UIRessourcesPanel::render () const
{
  if (!ImGui::Begin ("Ressources"))
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

  // print each resource name and quantity
  ImGui::Columns (3, nullptr, false);
  ImGui::SetColumnWidth (0, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (1, ImGui::GetWindowWidth () / 3);
  ImGui::SetColumnWidth (2, ImGui::GetWindowWidth () / 3);
  for (const auto &resource : Ressource::RessourceTypes)
    {
      if (!gData->getAchievementsView ()->isUnlocked (resource))
        continue;
      ImGui::SetCursorPosX (ImGui::GetCursorPosX ()
                            + ImGui::GetStyle ().ItemSpacing.x);
      ImGui::Text (
          "%s",
          gData->getRessourcesView ()->getRessourceName (resource).data ());

      ImGui::SameLine ();
      ImGui::NextColumn ();

      std::ostringstream stream;
      stream << std::fixed;
      stream << std::setprecision (2);
      stream << gData->getRessourcesView ()->getRessourceQuantity (resource)
             << "/"
             << gData->getRessourcesView ()->getRessourceMaxQuantity (
                    resource);

      std::string text = stream.str ();
      auto textWidth = ImGui::CalcTextSize (text.c_str ()).x;
      auto columnWidth
          = ImGui::GetColumnWidth () - ImGui::GetStyle ().ItemSpacing.x;
      ImGui::SetCursorPosX (ImGui::GetCursorPosX () + columnWidth - textWidth);
      ImGui::Text ("%s", text.c_str ());

      ImGui::SameLine ();
      ImGui::NextColumn ();

      std::string production = fmt::format (
          "+{}/sec",
          (gData->getRessourcesView ()->getRessourceProduction (resource)
           - gData->getRessourcesView ()->getRessourceConsumption (resource))
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