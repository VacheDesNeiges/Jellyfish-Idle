#pragma once

#include "GameIDsTypes.hpp"

#include <memory>
#include <optional>
#include <span>
#include <utility>
#include <vector>

class GardenManager;

class GardenDataView
{
public:
  explicit GardenDataView (std::shared_ptr<GardenManager>);
  std::string getName (AquaCultureID) const;
  unsigned getAssignedFieldsToCulture (AquaCultureID) const;
  bool isOngoing (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldConsumption (AquaCultureID,
                           std::optional<unsigned> = std::nullopt) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldProduction (AquaCultureID,
                          std::optional<unsigned> = std::nullopt) const;

  std::span<const AquaCultureID> getCultureTypes () const;

private:
  std::shared_ptr<GardenManager> garden;
};