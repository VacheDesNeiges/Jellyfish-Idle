#pragma once

#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"

#include <array>
#include <string>
#include <utility>
#include <vector>

enum class AquaCultureID
{
  Plankton,
  Oysters,
};

class AquaCulture final : public SaveAndLoadable<std::vector<int> >
{
public:
  explicit AquaCulture (AquaCultureID);
  ~AquaCulture () override = default;

  void start ();
  void cancel ();
  bool tick ();
  bool isDone () const;

  unsigned getRemainingTicks () const;
  unsigned getTotalRequiredTicks () const;

  std::vector<int> getData () const override;
  void loadData (const std::vector<int> &) override;

  static constexpr std::array<AquaCultureID, 2> CultureTypes = {
    AquaCultureID::Plankton,
    AquaCultureID::Oysters,
  };

private:
  bool cultureOngoing = false;
  bool done = false;
  unsigned baseTicksToFinish;
  unsigned remainingTicksToFinish;
  std::string name;

  std::vector<std::pair<RessourceType, double> > cost;
  std::vector<std::pair<RessourceType, double> > baseResult;
};