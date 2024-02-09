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

  RessourceStoneSlab,
  RessourceGlassPane,

  ResearchTabUnlocked,

  AncientOctopus,

  FocusingUpgradeBought,
  TelekinesisUpgradeBought,
  AdvancedTelekinesisUpgradeBought,

  LightningAbilityBuyable,
};

static constexpr std::array<AchievementIDs, 16> allAchievementsIDs
    = { AchievementIDs::PlanktonField,
        AchievementIDs::FirstSandNest,
        AchievementIDs::Mines,
        AchievementIDs::FirstJelly,
        AchievementIDs::JobMining,
        AchievementIDs::JobExploreTheDepths,
        AchievementIDs::JobArtisan,
        AchievementIDs::RessourceGlass,
        AchievementIDs::RessourceStoneSlab,
        AchievementIDs::RessourceGlassPane,
        AchievementIDs::ResearchTabUnlocked,
        AchievementIDs::AncientOctopus,
        AchievementIDs::FocusingUpgradeBought,
        AchievementIDs::TelekinesisUpgradeBought,
        AchievementIDs::AdvancedTelekinesisUpgradeBought,
        AchievementIDs::LightningAbilityBuyable };