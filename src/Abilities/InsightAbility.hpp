#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class InsightAbility
{
public:
  InsightAbility () = default;
  explicit InsightAbility (const nlohmann::json &);
  ~InsightAbility () = default;
  std::string getDescription () const;
  std::string getName () const;
  std::vector<std::pair<RessourceType, double> > getCost () const;
  std::vector<std::pair<RessourceType, double> > getProduction () const;

private:
  std::string name;
  std::string description;
  std::vector<std::pair<RessourceType, double> > castingCost;
  std::vector<std::pair<RessourceType, double> > ressourcesGained;

  friend class CallThunder;
};

class AbilityFactory
{
public:
  static std::unique_ptr<InsightAbility> createAbilityInstance (AbilityType t);
};