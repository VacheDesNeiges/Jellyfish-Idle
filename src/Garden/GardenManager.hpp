#pragma once
#include "AquaCulture.hpp"
#include "GameDataAccess.hpp"
#include "SaveAndLoadable.hpp"

#include <unordered_map>
#include <utility>
#include <vector>

class GardenManager final : public GameDataAccess,
                            public SaveAndLoadable<std::vector<int> >
{

public:
  GardenManager ();
  ~GardenManager () override = default;

  void startCulture (AquaCultureID);
  void cancelCulture (AquaCultureID);

  bool assign (AquaCultureID);
  bool unnasign (AquaCultureID);

  bool canAfford (AquaCultureID) const;
  bool isOngoing (AquaCultureID) const;

  std::string getName (AquaCultureID) const;

  unsigned getRemainingTicks (AquaCultureID) const;
  unsigned getTotalRequiredTicks (AquaCultureID) const;

  unsigned getTotalFields () const;
  unsigned getAssignedFields () const;
  unsigned getAssignedFieldsToCulture (AquaCultureID) const;

  bool tick ();
  std::vector<std::pair<RessourceType, double> > getCost (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getResult (AquaCultureID) const;
  std::vector<std::pair<RessourceType, double> > getFieldsResults ();

  void loadData (const std::vector<int> &) override;
  std::vector<int> getData () const override;

private:
  std::unordered_map<AquaCultureID, AquaCulture> cultures;
  std::unordered_map<AquaCultureID, unsigned> assignedFieldsToCultures;

  unsigned maxFields = 1;
};