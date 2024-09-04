#pragma once
#include <compare>
#include <cstddef>
#include <functional>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

enum class QuestLineEnum
{
    Octopus,
    Whale,
};

/**
 * @brief ID for the ressources type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 *
 */
struct RessourceType
{
    RessourceType() : value(0)
    {
    }

    constexpr explicit RessourceType(int intValue) : value(intValue){};

    friend std::strong_ordering operator<=>(const RessourceType &lhs,
                                            const RessourceType &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

inline void from_json(const nlohmann::json &json, RessourceType &rType)
{
    auto val = json.get<int>();
    rType = RessourceType(val);
}

inline void to_json(nlohmann::json &json, const RessourceType &rType)
{
    json = nlohmann::json{int(rType)};
}

template <>

struct std::hash<RessourceType>
{
    std::size_t operator()(const RessourceType &rType) const noexcept
    {
        return std::hash<int>{}(int(rType));
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
    BuildingType() : value(0)
    {
    }
    constexpr explicit BuildingType(int bType) : value(bType){};

    friend std::strong_ordering operator<=>(const BuildingType &lhs,
                                            const BuildingType &rhs) = default;
    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<BuildingType>
{
    std::size_t operator()(const BuildingType &bType) const noexcept
    {
        return std::hash<int>{}(int(bType));
    }
};

/**
 * @brief ID for the achievement Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AchievementIDs
{
    AchievementIDs() : value(0)
    {
    }
    constexpr explicit AchievementIDs(int achievID) : value(achievID){};

    friend std::strong_ordering operator<=>(
        const AchievementIDs &lhs, const AchievementIDs &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<AchievementIDs>
{
    std::size_t operator()(const AchievementIDs &achievID) const noexcept
    {
        return std::hash<int>{}(int(achievID));
    }
};

/**
 * @brief ID for the achievement Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AbilityType
{
    AbilityType() : value(0)
    {
    }
    constexpr explicit AbilityType(int abiType) : value(abiType){};

    friend std::strong_ordering operator<=>(const AbilityType &lhs,
                                            const AbilityType &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<AbilityType>
{
    std::size_t operator()(const AbilityType &abiType) const noexcept
    {
        return std::hash<int>{}(int(abiType));
    }
};

/**
 * @brief ID for the job Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct JellyJob
{
    JellyJob() : value(0)
    {
    }
    constexpr explicit JellyJob(int jJob) : value(jJob){};

    friend std::strong_ordering operator<=>(const JellyJob &lhs,
                                            const JellyJob &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<JellyJob>
{
    std::size_t operator()(const JellyJob &jJob) const noexcept
    {
        return std::hash<int>{}(int(jJob));
    }
};

/**
 * @brief ID for the Aquaculture Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct AquaCultureID
{
    AquaCultureID() : value(0)
    {
    }
    constexpr explicit AquaCultureID(int cultureID) : value(cultureID){};

    friend std::strong_ordering operator<=>(const AquaCultureID &lhs,
                                            const AquaCultureID &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<AquaCultureID>
{
    std::size_t operator()(const AquaCultureID &cultureID) const noexcept
    {
        return std::hash<int>{}(int(cultureID));
    }
};

/**
 * @brief ID for the Upgrade Type
 * Implements comparaison operators and hash function for use in std::map
 * the underlying value is an int
 */
struct UpgradeID
{
    UpgradeID() : value(0)
    {
    }
    constexpr explicit UpgradeID(int upgrID) : value(upgrID){};

    friend std::strong_ordering operator<=>(const UpgradeID &lhs,
                                            const UpgradeID &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<UpgradeID>
{
    std::size_t operator()(const UpgradeID &upgrID) const noexcept
    {
        return std::hash<int>{}(int(upgrID));
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

    RecipeID() : value(0)
    {
    }
    constexpr explicit RecipeID(int recipeID) : value(recipeID){};

    friend std::strong_ordering operator<=>(const RecipeID &lhs,
                                            const RecipeID &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<RecipeID>
{
    std::size_t operator()(const RecipeID &recipeID) const noexcept
    {
        return std::hash<int>{}(int(recipeID));
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

    MultiplierID() : value(0)
    {
    }
    constexpr explicit MultiplierID(int multID) : value(multID){};

    friend std::strong_ordering operator<=>(const MultiplierID &lhs,
                                            const MultiplierID &rhs) = default;

    constexpr explicit operator int() const
    {
        return value;
    }

  private:
    int value;
};

template <>

struct std::hash<MultiplierID>
{
    std::size_t operator()(const MultiplierID &multID) const noexcept
    {
        return std::hash<int>{}(int(multID));
    }
};

namespace RessourcesAlias
{
constexpr inline RessourceType FOOD{1};
constexpr inline RessourceType SAND{2};
constexpr inline RessourceType STONE{3};
constexpr inline RessourceType INSIGHT{4};
constexpr inline RessourceType GLASS{5};

constexpr inline RessourceType PEARL{1001};

constexpr inline RessourceType GLASSPANE{2001};
constexpr inline RessourceType STONESLAB{2002};
constexpr inline RessourceType KNOWLEDGETABLET{2003};
} // namespace RessourcesAlias

namespace BuildingsAlias
{
constexpr inline BuildingType AQUATICFIELD{1};
constexpr inline BuildingType DUNESHELTER{2};
constexpr inline BuildingType MINES{3};
constexpr inline BuildingType GLASSNESTS{4};
} // namespace BuildingsAlias

namespace AchievementsAlias
{
constexpr inline AchievementIDs JOBSYSTEM{3000};
constexpr inline AchievementIDs JELLYFISHLURING(3001);

constexpr inline AchievementIDs ABILITYSYSTEM{5006};

constexpr inline AchievementIDs DEPTHSYSTEM{4000};
constexpr inline AchievementIDs GARDENSYSTEM{2000};
constexpr inline AchievementIDs OCTOPUS{5000};

constexpr inline AchievementIDs ADVANCEDTELEKINESIS{5004};

constexpr inline AchievementIDs ANYRARERESSOURCE{6000};
constexpr inline AchievementIDs ANYMANUFACTUREDRESSOURCE{6001};

} // namespace AchievementsAlias

namespace JobsAlias
{
constexpr inline JellyJob NONE{0};
constexpr inline JellyJob MINING{1};
constexpr inline JellyJob EXPLORE{2};
constexpr inline JellyJob FOCUS{3};
constexpr inline JellyJob ARTISAN{4};
} // namespace JobsAlias

namespace CulturesAlias
{
constexpr inline AquaCultureID NONE{0};
} // namespace CulturesAlias

namespace UpgradesAlias
{
constexpr inline UpgradeID ADVANCEDTELEKINESIS{3};
constexpr inline UpgradeID LEVELING{4};
} // namespace UpgradesAlias

namespace RecipesAlias
{
constexpr inline RecipeID NONE{0};
constexpr inline RecipeID STONESLAB{1};
constexpr inline RecipeID GLASSPANE{2};
} // namespace RecipesAlias
