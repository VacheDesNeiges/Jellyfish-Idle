#include "SaveSystem.hpp"
#include "Building.hpp"
#include "Ressource.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

void
SaveSystem::save (
    const std::vector<std::pair<BuildingType, unsigned> > &buildingsData)
{
  nlohmann::json j;
  for (const auto &[type, quant] : buildingsData)
    {
      j["Building"]
          += { { "id", static_cast<unsigned> (type) }, { "Quantity", quant } };
    }

  std::ofstream file ("save.json");
  file << j;
}

void
SaveSystem::loadFromFile ()
{
  std::vector<std::pair<BuildingType, unsigned> > result;

  std::ifstream f ("save.json");
  nlohmann::json data = nlohmann::json::parse (f);

  for (const auto &d : data["Building"])
    {
      result.push_back (
          std::make_pair (static_cast<BuildingType> (d["id"].get<int> ()),
                          d["Quantity"].get<unsigned> ()));
    }
}