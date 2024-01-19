#include "UIUtils.hpp"
#include "fmt/core.h"
#include <cmath>

void
UIUtils::printCostsImGui (
    std::shared_ptr<GameDataView> gData,
    const std::vector<std::pair<RessourceType, double> > &ressourcesNeeded)

{
  if (ressourcesNeeded.empty ())
    return;

  ImVec4 textColor;
  ImGui::Text ("Price :\n");

  for (const auto &[ressource, cost] : ressourcesNeeded)
    {
      auto requestedQuantity
          = gData->getRessourcesView ()->getRessourceQuantity (ressource);
      auto ressourceName
          = gData->getRessourcesView ()->getRessourceName (ressource);
      std::string timeToBuyable = "";

      if (cost
          > gData->getRessourcesView ()->getRessourceMaxQuantity (ressource))
        {
          textColor = UIColors::redText;
        }
      else if (cost <= requestedQuantity)
        {
          textColor = UIColors::greenText;
        }
      else
        {
          textColor = UIColors::greyText;

          timeToBuyable += "( ";
          // TODO move to a function somewhere, also take care of the tick per
          // sec value that might change
          auto prodPerSec
              = (gData->getRessourcesView ()->getRessourceProduction (
                     ressource)
                 - gData->getRessourcesView ()->getRessourceConsumption (
                     ressource))
                * 2;

          auto missingRessources
              = cost
                - gData->getRessourcesView ()->getRessourceQuantity (
                    ressource);

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
                          fmt::format ("{} : {:.2f}/{:.2f}  {}", ressourceName,
                                       requestedQuantity, cost, timeToBuyable)
                              .c_str ());
    }
}