#pragma once
#include <memory>

class MultipliersRegister;
enum class MultiplierID;

class MultiplierDataView
{
public:
  explicit MultiplierDataView (std::shared_ptr<MultipliersRegister>);

  double getMultiplier (MultiplierID) const;

private:
  std::shared_ptr<MultipliersRegister> multipliers;
};