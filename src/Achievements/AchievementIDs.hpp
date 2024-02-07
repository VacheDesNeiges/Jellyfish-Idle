#pragma once

#include <array>

enum class AchievementIDs
{

  PlanktonField,
  FirstSandNest,
  Mines,

  FirstJelly,

  JobMining,
  JobExploreTheDepths,
  JobArtisan,

  RessourceGlass,

  ResearchTabUnlocked,

  AncientOctopus,

  FocusingUpgradeBought,
  TelekinesisUpgradeBought,
  AdvancedTelekinesisUpgradeBought,

  LightningAbilityBuyable,
};

static constexpr std::array<AchievementIDs, 14> allAchievementsIDs
    = { AchievementIDs::PlanktonField,
        AchievementIDs::FirstSandNest,
        AchievementIDs::Mines,
        AchievementIDs::FirstJelly,
        AchievementIDs::JobMining,
        AchievementIDs::JobExploreTheDepths,
        AchievementIDs::JobArtisan,
        AchievementIDs::RessourceGlass,
        AchievementIDs::ResearchTabUnlocked,
        AchievementIDs::AncientOctopus,
        AchievementIDs::FocusingUpgradeBought,
        AchievementIDs::TelekinesisUpgradeBought,
        AchievementIDs::AdvancedTelekinesisUpgradeBought,
        AchievementIDs::LightningAbilityBuyable };