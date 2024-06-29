#include "AquaCulture.hpp"
#include "AquaCultureID.hpp"
#include <cassert>
#include <vector>

AquaCulture::AquaCulture (AquaCultureID id)
{
  switch (id)
    {
      using namespace RessourcesAlias;
      using enum AquaCultureID;

    case Plankton:
      name = "Plankton";

      baseProduction.emplace_back (FOOD, 0.08);
      break;

    case SandWorms:
      name = "Sand Worms";

      baseConsumption.emplace_back (FOOD, 0.05);

      baseProduction.emplace_back (SAND, 0.05);
      break;

    case Oysters:
      name = "Oysters";

      baseConsumption.emplace_back (FOOD, 0.05);
      baseConsumption.emplace_back (SAND, 0.02);

      baseProduction.emplace_back (PEARL, 0.0017);
      break;

    default:
      assert (false);
    }
}

void
AquaCulture::start ()
{
  cultureOngoing = true;
}

void
AquaCulture::cancel ()
{
  cultureOngoing = false;
}

bool
AquaCulture::isOngoing () const
{
  return cultureOngoing;
}

CultureData
AquaCulture::getData () const
{
  CultureData result{
    result.craftOngoing = cultureOngoing,
    result.fieldCount = 0,
  };
  return result;
}

void
AquaCulture::loadData (const CultureData &data)
{
  cultureOngoing = data.craftOngoing;
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