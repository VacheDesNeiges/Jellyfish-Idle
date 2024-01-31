#pragma once
#include <memory>
#include <unordered_map>

enum class RessourceType;
struct SystemPtrs;

class GameSynchronizer
{
public:
  explicit GameSynchronizer (std::shared_ptr<SystemPtrs>);

  void gameTick () const;
  void synchronizeSystems () const;

private:
  std::shared_ptr<SystemPtrs> systems;

  void checkAchievements () const;
  void checkJellyfishArrival () const;
  void distributeExp () const;

  std::unordered_map<RessourceType, double>
  addMaps (const std::unordered_map<RessourceType, double> &,
           const std::unordered_map<RessourceType, double> &) const;
};