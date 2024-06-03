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
  SandWorms,
  None,
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
  bool isOngoing () const;
  bool canAfford () const;
  std::string getName () const;

  unsigned getRemainingTicks () const;
  unsigned getTotalRequiredTicks () const;

  std::vector<std::pair<RessourceType, double> > getCost () const;
  std::vector<std::pair<RessourceType, double> > getResult () const;

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
  unsigned remainingTicksToFinish = 0;
  std::string name;

  std::vector<std::pair<RessourceType, double> > cost;
  std::vector<std::pair<RessourceType, double> > baseResult;
};