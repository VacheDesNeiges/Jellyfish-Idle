#include "Ressource.hpp"
#include "gtest/gtest.h"
#include <cassert>

TEST (TestRessources, initialization)
{
  Ressource r (RessourceType::Food);
  ASSERT_EQ (r.getCurrentQuantity (), 0);
}

TEST (TestRessources, addAndSubstract)
{
  Ressource r (RessourceType::Food);
  ASSERT_GT (r.getMaxQuantity (), 10);
  r.add (10);
  ASSERT_EQ (r.getCurrentQuantity (), 10);
  r.add (-5);
  ASSERT_EQ (r.getCurrentQuantity (), 5);
}

TEST (TestRessources, overflow)
{
  Ressource r (RessourceType::Food);
  auto max = r.getMaxQuantity ();
  r.add (max + 10);
  ASSERT_EQ (r.getCurrentQuantity (), max);
}

TEST (TestRessources, underflow)
{
  Ressource r (RessourceType::Food);
  r.add (-5);
  ASSERT_EQ (r.getCurrentQuantity (), 0);
}