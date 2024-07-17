#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, RessourceFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::RessourcesPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class RessourceJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::RessourcesPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (RessourceJson_Fixture, IDUniqueness)
{
  std::set<RessourceType> idSet;

  for (const auto &ressource : json.at ("Ressources"))
    {
      const RessourceType id (ressource.at ("Id"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}