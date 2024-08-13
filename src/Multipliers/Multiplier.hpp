#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"

/**
 * @brief pure virtual class
 *
 */
class Multiplier : public GameDataAccess
{
  public:
    explicit Multiplier(double);
    virtual ~Multiplier() = default;
    virtual double getMultValue() const = 0;

    const double baseMultiplier;
};

class PerBuildingMultiplier : public Multiplier
{
  public:
    explicit PerBuildingMultiplier(double, BuildingType);
    double getMultValue() const override;

  private:
    const BuildingType bType;
};

class PerRessourceMultiplier : public Multiplier
{
  public:
    explicit PerRessourceMultiplier(double, RessourceType);
    double getMultValue() const override;

  private:
    const RessourceType rType;
};