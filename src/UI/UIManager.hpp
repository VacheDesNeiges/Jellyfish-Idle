#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
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
  void bindGameData (std::shared_ptr<GameDataSynchronizer>);

private:
  std::shared_ptr<GameDataSynchronizer> gData;
  UIRessourcesPanel ressourcesPanel;
  UIBuildingPanel buildingsPanel;
  UIJobsPanel jobsPanel;
  UIAbilitiesPanel abilitiesPanel;
  UIResearchPanel researchPanel;
};