#include "AquaCulture.hpp"

AquaCulture::AquaCulture (AquaCultureID id)
{
  switch (id)
    {
      using enum AquaCultureID;

    case Plankton:
      name = "Plankton";
      baseTicksToFinish = 120;

      baseResult.emplace_back (RessourceType::Food, 10);
      break;

    case Oysters:
      name = "Oyster";
      baseTicksToFinish = 600;

      cost.emplace_back (RessourceType::Food, 30);
      cost.emplace_back (RessourceType::Sand, 10);

      baseResult.emplace_back (RessourceType::Pearl, 1);
      break;

    default:
      break;
    }
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