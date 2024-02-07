#pragma once
#include "Ressource.hpp"

#include <memory>
#include <string>
#include <vector>

enum class AbilityType
{
  CallThunder
};

class InsightAbility
{
public:
  InsightAbility () = default;
  virtual ~InsightAbility () = default;
  virtual std::string getDescription () = 0;
  std::string getName () const;
  std::vector<std::pair<RessourceType, double> > getCost () const;
  std::vector<std::pair<RessourceType, double> > getProduction () const;

  static constexpr std::array<AbilityType, 1> AbilitiesTypes
      = { AbilityType::CallThunder };

private:
  std::string name;
  std::vector<std::pair<RessourceType, double> > castingCost;
  std::vector<std::pair<RessourceType, double> > ressourcesGained;

  friend class CallThunder;
};

class AbilityFactory
{
public:
  static std::unique_ptr<InsightAbility> createAbilityInstance (AbilityType t);
};