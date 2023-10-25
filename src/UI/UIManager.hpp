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
  void renderJobs () const;
};