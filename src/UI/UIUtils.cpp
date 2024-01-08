#include "UIUtils.hpp"
#include "fmt/core.h"

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

      if (cost
          > gData->getRessourcesView ()->getRessourceMaxQuantity (ressource))
        {
          textColor = UIColors::redText;
        }
      else if (cost < requestedQuantity)
        {
          textColor = UIColors::greenText;
        }
      else
        {
          textColor = UIColors::greyText;
        }
      ImGui::TextColored (textColor, "%s",
                          fmt::format ("{} : {:.2f}/{:.2f}", ressourceName,
                                       requestedQuantity, cost)
                              .c_str ());
    }
}