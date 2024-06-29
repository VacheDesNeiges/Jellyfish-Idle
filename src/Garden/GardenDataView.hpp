#pragma once

#include <memory>
#include <optional>
#include <utility>
#include <vector>

class GardenManager;
enum class AquaCultureID;
using RessourceType = int;

class GardenDataView
{
public:
  explicit GardenDataView (std::shared_ptr<GardenManager>);
  std::string getName (AquaCultureID) const;
  unsigned getAssignedFieldsToCulture (AquaCultureID) const;
  bool isOngoing (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldConsumption (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldProduction (AquaCultureID,
                          std::optional<unsigned> = std::nullopt) const;

private:
  std::shared_ptr<GardenManager> garden;
};