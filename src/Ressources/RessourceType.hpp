#pragma once
using RessourceType = int;

/**
 * @brief Constants that represent specific ressources, keep in mind that they
 * have to be kept synchronized with the ressources.json file
 *
 */
namespace RessourcesAlias
{
constexpr inline RessourceType FOOD = 1;
constexpr inline RessourceType SAND = 2;
constexpr inline RessourceType STONE = 3;
constexpr inline RessourceType INSIGHT = 4;
constexpr inline RessourceType GLASS = 5;

constexpr inline RessourceType PEARL = 1001;

constexpr inline RessourceType GLASSPANE = 2001;
constexpr inline RessourceType STONESLAB = 2002;
constexpr inline RessourceType KNOWLEDGETABLET = 2003;
}