#include "InsightAbility.hpp"
#include "CallThunder.hpp"
#include <memory>

std::unique_ptr<InsightAbility>
AbilityFactory::createAbilityInstance (AbilityType t)
{
  switch (t)
    {
    case AbilityType::CallThunder:
      return std::make_unique<CallThunder> ();
    }
}