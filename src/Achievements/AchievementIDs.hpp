#pragma once

#include <array>

enum class AchievementIDs
{

  BuildingAquaticField,
  BuildingSandNest,
  BuildingMines,

  GardenSystem,
  CulturePlankton,
  CultureOyster,

  FirstJelly,
  JellyfishLuring,

  JobSystem,
  JobMining,
  JobExploreTheDepths,
  JobArtisan,

  RessourceFood,
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

inline constexpr std::array<AchievementIDs, 22> allAchievementsIDs = {
  AchievementIDs::BuildingAquaticField,
  AchievementIDs::BuildingSandNest,
  AchievementIDs::BuildingMines,

  AchievementIDs::GardenSystem,
  AchievementIDs::CulturePlankton,
  AchievementIDs::CultureOyster,

  AchievementIDs::FirstJelly,
  AchievementIDs::JellyfishLuring,

  AchievementIDs::JobSystem,
  AchievementIDs::JobMining,
  AchievementIDs::JobExploreTheDepths,
  AchievementIDs::JobArtisan,

  AchievementIDs::RessourceFood,
  AchievementIDs::RessourceGlass,
  AchievementIDs::RessourceStoneSlab,
  AchievementIDs::RessourceGlassPane,

  AchievementIDs::ResearchTabUnlocked,

  AchievementIDs::AncientOctopus,
  AchievementIDs::FocusingUpgradeBought,
  AchievementIDs::TelekinesisUpgradeBought,
  AchievementIDs::AdvancedTelekinesisUpgradeBought,

  AchievementIDs::LightningAbilityBuyable,
};

inline constexpr std::array<AchievementIDs, 2> achievementsWithNotification = {
  AchievementIDs::FirstJelly,
  AchievementIDs::RessourceFood,
};