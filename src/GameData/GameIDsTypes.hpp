#pragma once
#include <compare>
#include <functional>

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
 * @brief Constants that represent specific ressources, keep in mind that they
 * have to be kept synchronized with the ressources.json file
 *
 */
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