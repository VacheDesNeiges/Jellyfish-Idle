#include "MultipliersRegister.hpp"

#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "Multiplier.hpp"

#include "nlohmann/json.hpp"
#include <iostream>
#include <linux/limits.h>
#include <memory>
#include <nlohmann/json_fwd.hpp>

MultipliersRegister::MultipliersRegister ()
{
  const auto fstream = FilePaths::getFileStream (FilePaths::MultipliersPath);

  try
    {
      auto multipliersJson = nlohmann::json::parse (fstream);

      multipliers.reserve (multipliersJson.at ("Multipliers").size ());

      for (const auto &mult : multipliersJson["Multipliers"])
        {
          MultiplierID multID{ mult.at ("ID") };

          if (mult.at ("Source").contains ("PerBuildingID"))
            {
              multipliers[multID] = std::make_unique<PerBuildingMultiplier> (
                  mult.at ("BaseMultiplier"),
                  BuildingType (mult.at ("Source").at ("PerBuildingID")));
            }

          if (mult.at ("Multiplies").contains ("ProdOfRessourceID"))
            {
              RessourceType rType{
                mult.at ("Multiplies").at ("ProdOfRessourceID")
              };
              multipliersCategories.ressourceProd[rType].push_back (multID);
            }
          else if (mult.at ("Multiplies").contains ("ProdOfAllFields"))
            {
              multipliersCategories.allFieldsProd.push_back (multID);
            }
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing multipliers :\n" << e.what () << "\n";
      abort ();
    }
}

double
MultipliersRegister::getMultiplier (MultiplierID id) const
{
  return 1 + multipliers.at (id)->getMultValue ();
}

double
MultipliersRegister::getRessourceProdMultiplier (RessourceType rType) const
{
  double result = 1;

  if (const auto &multVectorIt
      = multipliersCategories.ressourceProd.find (rType);
      multVectorIt != multipliersCategories.ressourceProd.end ())
    {
      for (const auto mult : multVectorIt->second)
        {
          result += multipliers.at (mult)->getMultValue ();
        }
    }
  return result;
}

double
MultipliersRegister::getBuildingProdMultiplier (BuildingType bType) const
{
  double result = 1;
  if (const auto &multVectorIt
      = multipliersCategories.buildingProd.find (bType);
      multVectorIt != multipliersCategories.buildingProd.end ())
    {
      for (const auto mult : multVectorIt->second)
        {
          result += multipliers.at (mult)->getMultValue ();
        }
    }
  return result;
}

double
MultipliersRegister::getAllFieldsMultiplier () const
{
  double result = 1;
  for (const auto &mult : multipliersCategories.allFieldsProd)
    {
      result += multipliers.at (mult)->getMultValue ();
    }
  return result;
}