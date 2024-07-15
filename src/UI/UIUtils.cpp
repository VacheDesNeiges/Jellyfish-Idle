#include "UIUtils.hpp"
#include "RessourceDataView.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include <cmath>

void
UIUtils::setBaseUITheme ()
{
  ImGuiStyle &style = ImGui::GetStyle ();
  style.SeparatorTextAlign = { 0.5, 0.5 };
  style.FrameRounding = 5.f;
  style.FramePadding = { 20.f, 3.f };
  style.WindowRounding = 5.f;
  style.WindowMenuButtonPosition = ImGuiDir_None;
  style.TabBarBorderSize = 0;
  style.TabRounding = 0;

  ImVec4 *colors = ImGui::GetStyle ().Colors;

  colors[ImGuiCol_Border] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_Text] = UIColors::RegularText;

  colors[ImGuiCol_ModalWindowDimBg] = UIColors::Dimming;

  colors[ImGuiCol_WindowBg] = UIColors::FullyTransparent;
  colors[ImGuiCol_PopupBg] = UIColors::NotificationBG;

  colors[ImGuiCol_Button] = UIColors::Buttons;
  colors[ImGuiCol_ButtonHovered] = UIColors::HoveredElements;
  colors[ImGuiCol_ButtonActive] = UIColors::ActivatedElement;

  colors[ImGuiCol_TitleBg] = UIColors::FullyTransparent;
  colors[ImGuiCol_TitleBgActive] = UIColors::FullyTransparent;
  colors[ImGuiCol_Separator] = UIColors::UnfocusedTransparentElement;

  colors[ImGuiCol_FrameBg] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_PlotHistogram] = UIColors::ActivatedTransparentElement;

  colors[ImGuiCol_TitleBgActive] = UIColors::FullyTransparent;

  colors[ImGuiCol_TabUnfocused] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_TabUnfocusedActive] = UIColors::ActivatedTransparentElement;

  colors[ImGuiCol_TabActive] = UIColors::ActivatedTransparentElement;

  colors[ImGuiCol_Tab] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_TabHovered] = UIColors::ActivatedElement;

  colors[ImGuiCol_HeaderHovered] = UIColors::Buttons;
  colors[ImGuiCol_HeaderActive] = UIColors::Buttons;

  colors[ImGuiCol_TableHeaderBg] = UIColors::Buttons;
  colors[ImGuiCol_TableBorderLight] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_TableBorderStrong] = UIColors::UnfocusedTransparentElement;
  colors[ImGuiCol_TableRowBg] = UIColors::FullyTransparent;
  colors[ImGuiCol_TableRowBgAlt] = UIColors::Dimming;
}

void
UIUtils::printCostsImGui (
    std::shared_ptr<const RessourceDataView> rView,
    const std::vector<std::pair<RessourceType, double> > &ressourcesNeeded)

{
  if (ressourcesNeeded.empty ())
    return;

  ImVec4 textColor;

  for (const auto &[ressource, cost] : ressourcesNeeded)
    {
      auto requestedQuantity = rView->getRessourceQuantity (ressource);
      auto ressourceName = rView->getRessourceName (ressource);
      std::string timeToBuyable = "";

      if (cost > rView->getRessourceMaxQuantity (ressource))
        {
          textColor = UIColors::ErrorText;
        }
      else if (cost <= requestedQuantity)
        {
          textColor = UIColors::ValidText;
        }
      else
        {
          textColor = UIColors::GreyedText;

          timeToBuyable += "( ";
          // TODO move to a function somewhere, also take care of the tick per
          // sec value that might change
          auto prodPerSec = (rView->getRessourceProduction (ressource)
                             - rView->getRessourceConsumption (ressource))
                            * 2;

          auto missingRessources
              = cost - rView->getRessourceQuantity (ressource);

          auto secondsToRequestedQuantity = missingRessources / prodPerSec;

          if (secondsToRequestedQuantity >= 3600)
            {
              auto nbHours = std::floor (secondsToRequestedQuantity / 3600);
              secondsToRequestedQuantity -= (nbHours * 3600);
              timeToBuyable += fmt::format ("{} Hours ", nbHours);
            }

          if (secondsToRequestedQuantity >= 60)
            {
              auto nbMinutes = std::floor (secondsToRequestedQuantity / 60);
              secondsToRequestedQuantity -= (nbMinutes * 60);
              timeToBuyable += fmt::format ("{} Minutes ", nbMinutes);
            }

          if (secondsToRequestedQuantity >= 1)
            {
              timeToBuyable += fmt::format (
                  "{} Seconds ", std::floor (secondsToRequestedQuantity));
            }
          timeToBuyable += fmt::format (")");
        }
      ImGui::TextColored (textColor, "%s",
                          fmt::format ("{} : {:.3f}/{:.3f}  {}", ressourceName,
                                       requestedQuantity, cost, timeToBuyable)
                              .c_str ());
    }
}