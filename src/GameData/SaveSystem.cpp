#include "SaveSystem.hpp"
#include "Building.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

void
SaveSystem::save (
    const std::vector<std::pair<BuildingType, unsigned> > &buildingsData)
{
  nlohmann::json j;
  for (const auto &[type, quant] : buildingsData)
    {
      j["Building"][std::to_string (static_cast<unsigned> (type))]["Quantity"]
          = quant;
    }

  std::ofstream file ("save.json");
  file << j;
}