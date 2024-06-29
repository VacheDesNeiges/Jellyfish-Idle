#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include "gtest/gtest.h"
#include <cassert>

/* FIXME : Rewrite the tests

TEST (TestsRessources, initialization)
{
  Ressource r (RessourceType::Food);
  ASSERT_EQ (0, r.getCurrentQuantity ());
}

TEST (TestsRessources, addAndSubstract)
{
  Ressource r (RessourceType::Food);
  ASSERT_LT (10, r.getMaxQuantity ());
  r.add (10);
  ASSERT_EQ (10, r.getCurrentQuantity ());
  r.add (-5);
  ASSERT_EQ (5, r.getCurrentQuantity ());
}

TEST (TestsRessources, overflow)
{
  Ressource r (RessourceType::Food);
  auto max = r.getMaxQuantity ();
  r.add (max + 10);
  ASSERT_EQ (max, r.getCurrentQuantity ());
}

TEST (TestsRessources, underflow)
{
  Ressource r (RessourceType::Food);
  r.add (-5);
  ASSERT_EQ (0, r.getCurrentQuantity ());
}

TEST (TestsRessources, setQuant)
{
  Ressource r (RessourceType::Food);
  r.setQuantity (25);
  ASSERT_EQ (25, r.getCurrentQuantity ());
}

TEST (TestsRessources, productionFunctions)
{
  Ressource r (RessourceType::Food);
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

TEST (TestsRessourceManager, initialization)
{
  RessourceManager rManager;
  for (const auto &r : Ressource::RessourceTypes)
    {
      ASSERT_EQ (0, rManager.getCurrentQuantity (r));
    }
}

TEST (TestsRessourceManager, addFunction)
{
  RessourceManager rManager;
  for (const auto &r : Ressource::RessourceTypes)
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
  for (const auto &r : Ressource::RessourceTypes)
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
  for (const auto &r : Ressource::RessourceTypes)
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
  for (const auto &r : Ressource::RessourceTypes)
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

// TODO : Consume & Produce Tests


*/