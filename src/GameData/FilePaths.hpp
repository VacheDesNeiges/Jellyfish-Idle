#pragma once

#include <cassert>
#include <fstream>
#include <linux/limits.h>
#include <string>
#include <string_view>
#include <unistd.h>

namespace FilePaths
{
inline constexpr std::string_view FontPath = "/assets/font/OpenSans-Bold.ttf";
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

inline std::string_view
getPath ()
{
  static std::string path;
  if (!path.empty ())
    return path;

  path.resize (PATH_MAX);

  if (ssize_t len = ::readlink ("/proc/self/exe\0", &path[0], PATH_MAX - 1);
      len != -1)
    {
      path.resize (static_cast<unsigned long> (len));

      if (std::size_t found = path.rfind ('/'); found != std::string::npos)
        path.resize (found);
      return path;
    }
  assert (false);
}

inline std::ifstream
getFileStream (std::string_view jsonPath)
{
  const auto path{ std::string (getPath ()) + std::string (jsonPath) };
  return std::ifstream (path);
}

}