#include "Ressource.hpp"
#include "gtest/gtest.h"
#include <cassert>

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