#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include <utility>
#include <vector>

class Achievement : public GameDataAccess
{
public:
  bool isUnlocked () const;
  bool unlockConditionMet () const;
  void unlock ();
  void setState (bool);

private:
  bool unlocked = false;

  unsigned jfishNumCondition = 0;
  std::vector<std::pair<RessourceType, int> > ressourceCondition;
  std::vector<std::pair<BuildingType, unsigned> > buildingsCondition;

  bool ressourcesConditionsMet () const;
  bool buildingConditionsMet () const;
};
