#include "Building.hpp"
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "InputHandler.hpp"
#include "Jellyfish.hpp"
#include "UIAbilitiesPanel.hpp"
#include "UIBuildingsPanel.hpp"
#include "UIJobsPanel.hpp"
#include "UIResearchPanel.hpp"
#include "UIRessourcesPanel.hpp"
#include "imgui.h"
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
};