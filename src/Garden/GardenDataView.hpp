#pragma once

#include <memory>

class GardenManager;
enum class AquaCultureID;

class GardenDataView
{
public:
  explicit GardenDataView (std::shared_ptr<GardenManager>);
  std::string getName (AquaCultureID) const;

private:
  std::shared_ptr<GardenManager> garden;
};