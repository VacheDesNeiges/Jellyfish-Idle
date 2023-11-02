#pragma once

#include "InsightAbility.hpp"
#include <string>

class CallThunder : public InsightAbility
{
public:
  explicit CallThunder ();
  ~CallThunder () override = default;
  std::string getDescription () override;
};