#include "Building.hpp"
#include "Jellyfish.hpp"
#include "imgui.h"
#include <memory>
#include <src/GameData/GameDataSynchronizer.hpp>

class UIManager
{
public:
  void renderUI () const;
  void bindGameData (std::shared_ptr<GameDataSynchronizer>);

private:
  std::shared_ptr<GameDataSynchronizer> gData;
  void renderRessources () const;

  void renderBuildings () const;
  bool renderBuildingButton (BuildingType) const;

  void renderJobs () const;
  void renderJobsControls (JellyJobs) const;
};