#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <set>

TEST (jsonTests, AchievementFileCanBeRead)
{
  const auto fstream = FilePaths::getFileStream (FilePaths::AchievementsPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class AchievementsJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    const auto fstream
        = FilePaths::getFileStream (FilePaths::AchievementsPath);

    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (AchievementsJson_Fixture, IDUniqueness)
{
  std::set<AchievementIDs> idSet;

  for (const auto &achievement : json.at ("Achievements"))
    {
      const AchievementIDs id (achievement.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}