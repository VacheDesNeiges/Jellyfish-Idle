#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, JobsFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::JobsPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class JobsJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::JobsPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (JobsJson_Fixture, IDUniqueness)
{
  std::set<JellyJob> idSet;

  for (const auto &job : json.at ("Jobs"))
    {
      const JellyJob id (job.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}