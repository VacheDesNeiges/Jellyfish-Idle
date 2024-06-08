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

      baseProduction.emplace_back (Food, 0.08);
      break;

    case Oysters:
      name = "Oysters";
      baseTicksToFinish = 600;

      baseConsumption.emplace_back (Food, 0.05);
      baseConsumption.emplace_back (Sand, 0.02);

      baseProduction.emplace_back (Pearl, 0.0017);
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

void
AquaCulture::reset ()
{
  done = false;
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

CultureData
AquaCulture::getData () const
{
  CultureData result{
    result.craftOngoing = cultureOngoing,
    result.craftDone = done,
    result.remainingTicksToEnd = remainingTicksToFinish,
    result.fieldCount = 0,
  };
  return result;
}

void
AquaCulture::loadData (const CultureData &data)
{
  done = data.craftDone;
  cultureOngoing = data.craftOngoing;
  remainingTicksToFinish = data.remainingTicksToEnd;
}

std::vector<std::pair<RessourceType, double> >
AquaCulture::getBaseConsumption () const
{
  return baseConsumption;
}

std::vector<std::pair<RessourceType, double> >
AquaCulture::getBaseProduction () const
{
  return baseProduction;
}

std::string
AquaCulture::getName () const
{
  return name;
}