#pragma once
#include "AquaCulture.hpp"
#include "AquaCultureID.hpp"
#include "GameDataAccess.hpp"
#include "SaveAndLoadable.hpp"

#include <unordered_map>
#include <utility>
#include <vector>

class GardenManager final
    : public GameDataAccess,
      public SaveAndLoadable<
          std::vector<std::pair<AquaCultureID, CultureData> > >
{

public:
  GardenManager ();
  ~GardenManager () override = default;

  void startCulture (AquaCultureID);
  void cancelCulture (AquaCultureID);

  bool assign (AquaCultureID);
  bool unnasign (AquaCultureID);

  bool canAffordTick (AquaCultureID) const;
  bool isOngoing (AquaCultureID) const;

  std::string getName (AquaCultureID) const;

  unsigned getTotalFields () const;
  unsigned getAssignedFields () const;
  unsigned getAssignedFieldsToCulture (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getConsumption (AquaCultureID) const;
  std::vector<std::pair<RessourceType, double> >
      getProduction (AquaCultureID) const;

  void loadData (
      const std::vector<std::pair<AquaCultureID, CultureData> > &) override;

  std::vector<std::pair<AquaCultureID, CultureData> >
  getData () const override;

private:
  std::unordered_map<AquaCultureID, AquaCulture> cultures;
  std::unordered_map<AquaCultureID, unsigned> assignedFieldsToCultures;

  unsigned maxFields = 1;
};