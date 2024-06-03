#include "AquaCulture.hpp"
#include <cassert>
#include <vector>

AquaCulture::AquaCulture (AquaCultureID id)
{
  switch (id)
    {
      using enum RessourceType;
      using enum AquaCultureID;

    case Plankton:
      name = "Plankton";
      baseTicksToFinish = 120;

      baseResult.emplace_back (Food, 10);
      break;

    case Oysters:
      name = "Oyster";
      baseTicksToFinish = 600;

      cost.emplace_back (Food, 30);
      cost.emplace_back (Sand, 10);

      baseResult.emplace_back (Pearl, 1);
      break;

    default:
      assert (false);
    }
  remainingTicksToFinish = baseTicksToFinish;
}

void
AquaCulture::start ()
{
  cultureOngoing = true;
  remainingTicksToFinish = baseTicksToFinish;
}

void
AquaCulture::cancel ()
{
  cultureOngoing = false;
  remainingTicksToFinish = baseTicksToFinish;
}

bool
AquaCulture::tick ()
{
  if (cultureOngoing)
    {
      remainingTicksToFinish--;
      if (remainingTicksToFinish == 0)
        {
          done = true;
          cultureOngoing = false;
        }
    }
  return done;
}

bool
AquaCulture::isDone () const
{
  return done;
}

bool
AquaCulture::isOngoing () const
{
  return cultureOngoing;
}

unsigned
AquaCulture::getRemainingTicks () const
{
  return remainingTicksToFinish;
}

unsigned
AquaCulture::getTotalRequiredTicks () const
{
  return baseTicksToFinish;
}

std::vector<int>
AquaCulture::getData () const
{
  // TODO implement
  return { 1 };
}

void
AquaCulture::loadData (const std::vector<int> &vec)
{
  // TODO Implement
  vec.at (0);
}

std::vector<std::pair<RessourceType, double> >
AquaCulture::getCost () const
{
  return cost;
}

std::vector<std::pair<RessourceType, double> >
AquaCulture::getResult () const
{ // TODO multipliers from garden level ?
  return baseResult;
}

bool
AquaCulture::canAfford () const
{
  // TODO : implement
  return false;
}

std::string
AquaCulture::getName () const
{
  return name;
}