#pragma once

#include "AquaCultureID.hpp"
#include "GameIDsTypes.hpp"
#include "SaveAndLoadable.hpp"

#include <array>
#include <string>
#include <utility>
#include <vector>

struct CultureData
{
  bool craftOngoing;
  unsigned fieldCount;
};

class AquaCulture final : public SaveAndLoadable<CultureData>
{
public:
  explicit AquaCulture (AquaCultureID);
  ~AquaCulture () override = default;

  void start ();
  void cancel ();
  bool isOngoing () const;
  std::string getName () const;

  std::vector<std::pair<RessourceType, double> > getBaseConsumption () const;
  std::vector<std::pair<RessourceType, double> > getBaseProduction () const;

  CultureData getData () const override;
  void loadData (const CultureData &) override;

  static constexpr std::array<AquaCultureID, 3> CultureTypes = {
    AquaCultureID::Plankton,
    AquaCultureID::SandWorms,
    AquaCultureID::Oysters,
  };

private:
  bool cultureOngoing = false;
  std::string name;

  std::vector<std::pair<RessourceType, double> > baseProduction;
  std::vector<std::pair<RessourceType, double> > baseConsumption;
};