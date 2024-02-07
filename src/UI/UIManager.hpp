#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "InputHandler.hpp"
#include "UIAbilitiesPanel.hpp"
#include "UIBuildingsPanel.hpp"
#include "UIDepthPanel.hpp"
#include "UIJobsPanel.hpp"
#include "UIOctopusPanel.hpp"
#include "UIResearchPanel.hpp"
#include "UIRessourcesPanel.hpp"

#include <memory>

class UIManager
{
public:
  void renderUI () const;
  void bindGameData (std::shared_ptr<GameDataView>,
                     std::shared_ptr<InputHandler>);

private:
  std::shared_ptr<GameDataView> gData = nullptr;
  std::shared_ptr<InputHandler> inputHandler = nullptr;

  UIRessourcesPanel ressourcesPanel;
  UIBuildingPanel buildingsPanel;
  UIJobsPanel jobsPanel;
  UIAbilitiesPanel abilitiesPanel;
  UIResearchPanel researchPanel;
  UIDepthPanel depthPanel;
  UIOctopusPanel octopusPanel;
};