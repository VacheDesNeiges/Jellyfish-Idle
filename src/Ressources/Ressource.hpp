#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

class Ressource
{

  public:
    Ressource() = default;
    explicit Ressource(const nlohmann::json &);
    ~Ressource() = default;
    void add(double n);
    double getCurrentQuantity() const;
    double getMaxQuantity() const;
    double getNetProduction() const;
    double getProduction() const;
    double getConsumption() const;
    std::string_view getName() const;
    void resetValuesPerTick();
    void addToConsumptionPerTick(double);
    void addToProdPerTick(double);
    void setQuantity(double);
    void setBonusMaxQuantity(double);

  private:
    std::string name;
    double quantity = 0;
    double baseMaxQuantity = -1;
    double maxQuantity = -1;

    double prodPerTick = 0;
    double consumptionPerTick = 0;
};