#include "Ressource.hpp"
#include <string_view>

Ressource::Ressource (RessourceType rType)
{

  switch (rType)
    {
    case RessourceType::Food:
      name = "Food";
      max_quantity = 200;
      quantity = 0;
      base_production = 0.005f;
      break;

    case RessourceType::Minerals:
      name = "Minerals";
      max_quantity = 300;
      quantity = 0;
      base_production = 0;
      break;

    case RessourceType::SeaShells:
      name = "Sea Shells";
      max_quantity = 500;
      quantity = 0;
      base_production = 0;
      break;

    default:
      break;
    }
}

void
Ressource::update (unsigned int nbTicks)
{
  quantity += (base_production * static_cast<float> (nbTicks));
  if (quantity > static_cast<float> (max_quantity))
    quantity = static_cast<float> (max_quantity);
  std::string s = name + " " + std::to_string (quantity) + "/"
                  + std::to_string (max_quantity) + "\n+"
                  + std::to_string (base_production) + " per sec";
}

void
Ressource::add (double n)
{
  if (quantity + n <= max_quantity)
    {
      quantity += n;
    }
  else
    {
      quantity = max_quantity;
    }
}

double
Ressource::getCurrentQuantity () const
{
  return quantity;
}

double
Ressource::getMaxQuantity () const
{
  return max_quantity;
}

std::string_view
Ressource::getName () const
{
  return name;
}