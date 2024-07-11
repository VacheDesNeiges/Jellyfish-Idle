#pragma once
#include <compare>
#include <cstddef>
#include <functional>

/**
 * @brief ID for the ressources type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 *
 */
struct RessourceType
{
  int value;

  RessourceType () : value (0) {}
  constexpr explicit RessourceType (int x) : value (x){};

  friend std::strong_ordering operator<=> (const RessourceType &lhs,
                                           const RessourceType &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<RessourceType>
{
  std::size_t
  operator() (const RessourceType &r) const noexcept
  {
    return std::hash<int>{}(r.value);
  }
};

/**
 * @brief ID for the building type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 *
 */
struct BuildingType
{
  int value;
  BuildingType () : value (0) {}
  constexpr explicit BuildingType (int x) : value (x){};

  friend std::strong_ordering operator<=> (const BuildingType &lhs,
                                           const BuildingType &rhs)
      = default;
  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<BuildingType>
{
  std::size_t
  operator() (const BuildingType &b) const noexcept
  {
    return std::hash<int>{}(b.value);
  }
};

/**
 * @brief ID for the achievement Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AchievementIDs
{
  int value;
  AchievementIDs () : value (0) {}
  constexpr explicit AchievementIDs (int x) : value (x){};

  friend std::strong_ordering operator<=> (const AchievementIDs &lhs,
                                           const AchievementIDs &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<AchievementIDs>
{
  std::size_t
  operator() (const AchievementIDs &b) const noexcept
  {
    return std::hash<int>{}(b.value);
  }
};

/**
 * @brief ID for the achievement Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AbilityType
{
  int value;
  AbilityType () : value (0) {}
  constexpr explicit AbilityType (int x) : value (x){};

  friend std::strong_ordering operator<=> (const AbilityType &lhs,
                                           const AbilityType &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<AbilityType>
{
  std::size_t
  operator() (const AbilityType &a) const noexcept
  {
    return std::hash<int>{}(a.value);
  }
};

/**
 * @brief ID for the job Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct JellyJob
{
  int value;
  JellyJob () : value (0) {}
  constexpr explicit JellyJob (int x) : value (x){};

  friend std::strong_ordering operator<=> (const JellyJob &lhs,
                                           const JellyJob &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<JellyJob>
{
  std::size_t
  operator() (const JellyJob &a) const noexcept
  {
    return std::hash<int>{}(a.value);
  }
};

/**
 * @brief ID for the Aquaculture Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AquaCultureID
{
  int value;
  AquaCultureID () : value (0) {}
  constexpr explicit AquaCultureID (int x) : value (x){};

  friend std::strong_ordering operator<=> (const AquaCultureID &lhs,
                                           const AquaCultureID &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<AquaCultureID>
{
  std::size_t
  operator() (const AquaCultureID &a) const noexcept
  {
    return std::hash<int>{}(a.value);
  }
};

/**
 * @brief ID for the Upgrade Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct UpgradeID
{
  int value;
  UpgradeID () : value (0) {}
  constexpr explicit UpgradeID (int x) : value (x){};

  friend std::strong_ordering operator<=> (const UpgradeID &lhs,
                                           const UpgradeID &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<UpgradeID>
{
  std::size_t
  operator() (const UpgradeID &a) const noexcept
  {
    return std::hash<int>{}(a.value);
  }
};

/**
 * @brief ID for the recipe id type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 *
 */
struct RecipeID
{
  int value;

  RecipeID () : value (0) {}
  constexpr explicit RecipeID (int x) : value (x){};

  friend std::strong_ordering operator<=> (const RecipeID &lhs,
                                           const RecipeID &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<RecipeID>
{
  std::size_t
  operator() (const RecipeID &r) const noexcept
  {
    return std::hash<int>{}(r.value);
  }
};

/**
 * @brief ID for the multiplier ID type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 *
 */
struct MultiplierID
{
  int value;

  MultiplierID () : value (0) {}
  constexpr explicit MultiplierID (int x) : value (x){};

  friend std::strong_ordering operator<=> (const MultiplierID &lhs,
                                           const MultiplierID &rhs)
      = default;

  constexpr explicit operator int () const { return value; }
};

template <>

struct std::hash<MultiplierID>
{
  std::size_t
  operator() (const MultiplierID &r) const noexcept
  {
    return std::hash<int>{}(r.value);
  }
};

namespace RessourcesAlias
{
constexpr inline RessourceType FOOD{ 1 };
constexpr inline RessourceType SAND{ 2 };
constexpr inline RessourceType STONE{ 3 };
constexpr inline RessourceType INSIGHT{ 4 };
constexpr inline RessourceType GLASS{ 5 };

constexpr inline RessourceType PEARL{ 1001 };

constexpr inline RessourceType GLASSPANE{ 2001 };
constexpr inline RessourceType STONESLAB{ 2002 };
constexpr inline RessourceType KNOWLEDGETABLET{ 2003 };
}

namespace BuildingsAlias
{
constexpr inline BuildingType AQUATICFIELD{ 1 };
constexpr inline BuildingType DUNESHELTER{ 2 };
constexpr inline BuildingType MINES{ 3 };
constexpr inline BuildingType GLASSNESTS{ 4 };
}

namespace AchievementsAlias
{
constexpr inline AchievementIDs JOBSYSTEM{ 3000 };
constexpr inline AchievementIDs JELLYFISHLURING (3001);

constexpr inline AchievementIDs ABILITYSYSTEM{ 5006 };

constexpr inline AchievementIDs DEPTHSYSTEM{ 4000 };
constexpr inline AchievementIDs GARDENSYSTEM{ 2000 };
constexpr inline AchievementIDs OCTOPUS{ 5000 };

constexpr inline AchievementIDs ADVANCEDTELEKINESIS{ 5004 };

constexpr inline AchievementIDs ANYRARERESSOURCE{ 6000 };
constexpr inline AchievementIDs ANYMANUFACTUREDRESSOURCE{ 6001 };

}

namespace JobsAlias
{
constexpr inline JellyJob NONE{ 0 };
constexpr inline JellyJob MINING{ 1 };
constexpr inline JellyJob EXPLORE{ 2 };
constexpr inline JellyJob FOCUS{ 3 };
constexpr inline JellyJob ARTISAN{ 4 };
}

namespace CulturesAlias
{
constexpr inline AquaCultureID NONE{ 0 };
}

namespace UpgradesAlias
{
constexpr inline UpgradeID ADVANCEDTELEKINESIS{ 3 };
constexpr inline UpgradeID LEVELING{ 4 };
}

namespace RecipesAlias
{
constexpr inline RecipeID NONE{ 0 };
constexpr inline RecipeID STONESLAB{ 1 };
constexpr inline RecipeID GLASSPANE{ 2 };
}