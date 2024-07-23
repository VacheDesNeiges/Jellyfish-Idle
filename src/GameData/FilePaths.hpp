#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <linux/limits.h>
#include <string>
#include <string_view>
#include <unistd.h>

namespace FilePaths
{
inline constexpr std::string_view FontPath = "/assets/font/asap.ttf";

inline constexpr std::string_view RessourcesPath
    = "/assets/jsons/ressources.json";

inline constexpr std::string_view BuildingsPath
    = "/assets/jsons/buildings.json";
inline constexpr std::string_view JobsPath = "/assets/jsons/jobs.json";

inline constexpr std::string_view AchievementsPath
    = "/assets/jsons/achievements.json";

inline constexpr std::string_view UpgradesPath = "/assets/jsons/upgrades.json";

inline constexpr std::string_view AbilitiesPath
    = "/assets/jsons/abilities.json";

inline constexpr std::string_view CulturesPath = "/assets/jsons/cultures.json";
inline constexpr std::string_view RecipesPath = "/assets/jsons/recipes.json";

inline constexpr std::string_view MultipliersPath
    = "/assets/jsons/multipliers.json";

inline constexpr std::string_view QuestsPath = "/assets/jsons/quests.json";

inline std::string_view
getPath ()
{
  static std::string path;
  if (!path.empty ())
    return path;

  try
    {
      const std::filesystem::path currentpath
          = std::filesystem::read_symlink ("/proc/self/exe");
      path += currentpath.parent_path ().c_str ();
    }
  catch (const std::filesystem::filesystem_error &e)
    {
      std::cerr << "Error getting current path: " << e.what ();
      abort ();
    }
  return path;
}

inline std::ifstream
getFileStream (std::string_view jsonPath)
{
  const auto path{ std::string (getPath ()) + std::string (jsonPath) };
  return std::ifstream (path);
}

}