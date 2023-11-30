#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
#include "Jellyfish.hpp"
#include "UIBuildingsPanel.hpp"
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
  void renderRessources () const;
  void renderBuildings () const;
  bool renderBuildingButton (BuildingType) const;
  void renderJobs () const;
  void renderJobsControls (JellyJobs) const;
  void renderInsightAbilities () const;
  void renderResearch () const;
};