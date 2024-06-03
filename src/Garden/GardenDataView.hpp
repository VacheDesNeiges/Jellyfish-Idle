#pragma once

#include <memory>
#include <utility>
#include <vector>

class GardenManager;
enum class AquaCultureID;
enum class RessourceType;

class GardenDataView
{
public:
  explicit GardenDataView (std::shared_ptr<GardenManager>);
  std::string getName (AquaCultureID) const;
  unsigned getAssignedFieldsToCulture (AquaCultureID) const;
  bool isOngoing (AquaCultureID) const;
  bool canAfford (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldCost (AquaCultureID) const;

  std::vector<std::pair<RessourceType, double> >
      getFieldResults (AquaCultureID) const;

  unsigned getRemainingTicks (AquaCultureID) const;
  unsigned getTotalRequiredTicks (AquaCultureID) const;

private:
  std::shared_ptr<GardenManager> garden;
};