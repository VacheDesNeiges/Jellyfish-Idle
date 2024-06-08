#pragma once

#include "AquaCultureID.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"

#include <array>
#include <string>
#include <utility>
#include <vector>

struct CultureData
{
  bool craftOngoing;
  bool craftDone;
  unsigned remainingTicksToEnd;
  unsigned fieldCount;
};

class AquaCulture final : public SaveAndLoadable<CultureData>
{
public:
  explicit AquaCulture (AquaCultureID);
  ~AquaCulture () override = default;

  void start ();
  void cancel ();
  void reset ();
  bool tick ();
  bool isDone () const;
  bool isOngoing () const;
  std::string getName () const;

  unsigned getRemainingTicks () const;
  unsigned getTotalRequiredTicks () const;

  std::vector<std::pair<RessourceType, double> > getBaseConsumption () const;
  std::vector<std::pair<RessourceType, double> > getBaseProduction () const;

  CultureData getData () const override;
  void loadData (const CultureData &) override;

  static constexpr std::array<AquaCultureID, 2> CultureTypes = {
    AquaCultureID::Plankton,
    AquaCultureID::Oysters,
  };

private:
  bool cultureOngoing = false;
  bool done = false;
  unsigned baseTicksToFinish;
  unsigned remainingTicksToFinish = 0;
  std::string name;

  std::vector<std::pair<RessourceType, double> > baseProduction;
  std::vector<std::pair<RessourceType, double> > baseConsumption;
};