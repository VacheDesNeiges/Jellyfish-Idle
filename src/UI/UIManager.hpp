#include "imgui.h"
#include <memory>
#include <src/GameData/GameDataSynchronizer.hpp>

class UIManager
{
public:
  void renderUI () const;
  void bindGameData (std::shared_ptr<GameDataSynchronizer>);

private:
  void renderRessources () const;
  std::shared_ptr<GameDataSynchronizer> gData;
};