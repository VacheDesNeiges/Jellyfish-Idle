#pragma once

#include "Achievement.hpp"
#include "AchievementIDs.hpp"
#include "AquaCultureID.hpp"
#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Notification.hpp"
#include "SaveAndLoadable.hpp"
#include "UpgradeId.hpp"

#include <functional>
#include <optional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class AchievementSystem
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<AchievementIDs, bool> > >
{
public:
  AchievementSystem ();
  ~AchievementSystem () override = default;

  bool isUnlocked (AchievementIDs) const;
  bool isUnlocked (BuildingType) const;
  bool isUnlocked (JellyJobs) const;
  bool isUnlocked (RessourceType) const;
  bool isUnlocked (AbilityType) const;
  bool isUnlocked (UpgradeID) const;
  bool isUnlocked (AquaCultureID) const;

  void unlock (AchievementIDs);
  std::vector<std::pair<AchievementIDs, bool> > getData () const override;
  void
  loadData (const std::vector<std::pair<AchievementIDs, bool> > &) override;
  void checkAchievements ();

  std::optional<std::string_view> getNotification () const;
  void popNotification ();
  void pushNotification (AchievementIDs);

private:
  void initLambdas ();
  std::unordered_map<RessourceType, AchievementIDs> ressourcesAchievements;
  std::unordered_map<BuildingType, AchievementIDs> buildingsAchievements;
  std::unordered_map<AchievementIDs, Achievement> achievements;
  std::unordered_map<AchievementIDs, std::function<bool ()> >
      achievementConditions;

  std::unordered_map<AchievementIDs, Notification> notifications;

  std::queue<Notification> notificationQueue;
};