#pragma once
#include "Ressource.hpp"
#include <memory>
#include <string>

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