#include "FilePaths.hpp"
#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include "gtest/gtest.h"
#include <cassert>
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

class RessourcesTests_Fixture : public ::testing::Test
{
public:
  std::vector<Ressource> ressources;

  void
  SetUp () override
  {
    const auto path = std::string (FilePaths::getPath ())
                      + std::string (FilePaths::RessourcesPath);
    std::fstream fstream (path);
    const auto &json = nlohmann::json::parse (fstream);
    for (const auto &ressource : json.at ("Ressources"))
      {
        ressources.emplace_back (ressource);
      }

    for (const auto &rare : json.at ("RareRessources"))
      {
        ressources.emplace_back (rare);
      }

    for (const auto &manufactured : json.at ("ManufacturedRessources"))
      {
        ressources.emplace_back (manufactured);
      }
  }
};

TEST_F (RessourcesTests_Fixture, initialization)
{
  for (const auto &r : ressources)
    {
      ASSERT_EQ (0, r.getCurrentQuantity ());
    }
}

TEST_F (RessourcesTests_Fixture, addAndSubstract)
{
  for (auto &r : ressources)
    {
      ASSERT_LT (10, r.getMaxQuantity ());
      r.add (10);
      ASSERT_EQ (10, r.getCurrentQuantity ());
      r.add (-5);
      ASSERT_EQ (5, r.getCurrentQuantity ());
    }
}

TEST_F (RessourcesTests_Fixture, overflow)
{
  for (auto &r : ressources)
    {
      auto max = r.getMaxQuantity ();
      r.add (max + 10);
      ASSERT_EQ (max, r.getCurrentQuantity ());
    }
}

TEST_F (RessourcesTests_Fixture, underflow)
{
  for (auto &r : ressources)
    {
      r.add (-5);
      ASSERT_EQ (0, r.getCurrentQuantity ());
    }
}

TEST_F (RessourcesTests_Fixture, setQuant)
{
  for (auto &r : ressources)
    {
      r.setQuantity (25);
      ASSERT_EQ (25, r.getCurrentQuantity ());
    }
}

TEST_F (RessourcesTests_Fixture, productionFunctions)
{
  for (auto &r : ressources)
    {

      ASSERT_EQ (0, r.getProduction ());
      ASSERT_EQ (0, r.getConsumption ());
      ASSERT_EQ (0, r.getNetProduction ());

      r.addToProdPerTick (25);
      ASSERT_EQ (25, r.getNetProduction ());
      ASSERT_EQ (25, r.getProduction ());
      ASSERT_EQ (0, r.getConsumption ());

      r.addToConsumptionPerTick (10);
      ASSERT_EQ (15, r.getNetProduction ());
      ASSERT_EQ (25, r.getProduction ());
      ASSERT_EQ (10, r.getConsumption ());

      r.addToProdPerTick (25);
      ASSERT_EQ (40, r.getNetProduction ());
      ASSERT_EQ (50, r.getProduction ());
      ASSERT_EQ (10, r.getConsumption ());

      r.addToConsumptionPerTick (10);
      ASSERT_EQ (30, r.getNetProduction ());
      ASSERT_EQ (50, r.getProduction ());
      ASSERT_EQ (20, r.getConsumption ());

      r.resetValuesPerTick ();
      ASSERT_EQ (0, r.getNetProduction ());
      ASSERT_EQ (0, r.getProduction ());
      ASSERT_EQ (0, r.getConsumption ());
    }
}

TEST (TestsRessourceManager, initialization)
{
  RessourceManager rManager;
  for (const auto &r : rManager.getAllRessourceTypes ())
    {
      ASSERT_EQ (0, rManager.getCurrentQuantity (r));
    }
}

TEST (TestsRessourceManager, addFunction)
{
  RessourceManager rManager;
  for (const auto &r : rManager.getAllRessourceTypes ())
    {
      assert (rManager.getMaxQuantity (r) > 10);

      ASSERT_EQ (0, rManager.getCurrentQuantity (r));
      rManager.add (r, 10);
      ASSERT_EQ (10, rManager.getCurrentQuantity (r));
      rManager.add (r, -5);
      ASSERT_EQ (5, rManager.getCurrentQuantity (r));
    }
}

TEST (TestsRessourceManager, addOverflow)
{
  RessourceManager rManager;
  for (const auto &r : rManager.getAllRessourceTypes ())
    {
      const auto rMax = rManager.getMaxQuantity (r);
      rManager.add (r, rMax);
      ASSERT_EQ (rMax, rManager.getCurrentQuantity (r));
      rManager.add (r, 5);
      ASSERT_EQ (rMax, rManager.getCurrentQuantity (r));

      rManager.add (r, -5);
      ASSERT_EQ (rMax - 5, rManager.getCurrentQuantity (r));
    }
}

TEST (TestsRessourceManager, addUnderflow)
{
  RessourceManager rManager;
  for (const auto &r : rManager.getAllRessourceTypes ())
    {
      ASSERT_EQ (0, rManager.getCurrentQuantity (r));
      rManager.add (r, -5);
      ASSERT_EQ (0, rManager.getCurrentQuantity (r));

      rManager.add (r, 5);
      ASSERT_EQ (5, rManager.getCurrentQuantity (r));
    }
}

TEST (TestsRessourceManager, productionFunctions)
{
  RessourceManager rManager;
  for (const auto &r : rManager.getAllRessourceTypes ())
    {
      ASSERT_EQ (0, rManager.getProduction (r));
      ASSERT_EQ (0, rManager.getConsumption (r));
      ASSERT_EQ (0, rManager.getNetProduction (r));

      rManager.addToProdPerTick (r, 25);
      ASSERT_EQ (25, rManager.getNetProduction (r));
      ASSERT_EQ (25, rManager.getProduction (r));
      ASSERT_EQ (0, rManager.getConsumption (r));

      rManager.addToProdPerTick (r, -10);
      ASSERT_EQ (15, rManager.getNetProduction (r));
      ASSERT_EQ (25, rManager.getProduction (r));
      ASSERT_EQ (10, rManager.getConsumption (r));

      rManager.addToProdPerTick (r, 25);
      ASSERT_EQ (40, rManager.getNetProduction (r));
      ASSERT_EQ (50, rManager.getProduction (r));
      ASSERT_EQ (10, rManager.getConsumption (r));

      rManager.addToProdPerTick (r, -10);
      ASSERT_EQ (30, rManager.getNetProduction (r));
      ASSERT_EQ (50, rManager.getProduction (r));
      ASSERT_EQ (20, rManager.getConsumption (r));

      rManager.zerosValuePerTick ();
      ASSERT_EQ (0, rManager.getNetProduction (r));
      ASSERT_EQ (0, rManager.getProduction (r));
      ASSERT_EQ (0, rManager.getConsumption (r));
    }
}
