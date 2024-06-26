#include "RessourceManager.hpp"
#include "FilePaths.hpp"
#include "Ressource.hpp"
#include "RessourceType.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

RessourceManager::RessourceManager () { init (); }

void
RessourceManager::init ()
{
  std::cout << "Starting to read ressources \n";
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::RessourcesPath);

  std::ifstream fstream (path);
  std::cout << "Path = " << path << "\n";

  nlohmann::json ressourcesJson = nlohmann::json::parse (fstream);
  std::cout << "Parsing OK \n";

  ressources.reserve (ressourcesJson["Ressources"].size ()
                      + ressourcesJson["RareRessources"].size ()
                      + ressourcesJson["ManufacturedRessources"].size ());

  Ressource::ressourceTypes.reserve (ressourcesJson["Ressources"].size ());

  std::cout << "First Loop\n";

  for (const auto &resData : ressourcesJson["Ressources"])
    {
      ressources.try_emplace (resData.value ("Id", -1),
                              resData.value ("Name", "Unknown"),
                              resData.value ("Max_Quantity", -1));

      Ressource::ressourceTypes.push_back (resData.value ("Id", -1));
    }

  Ressource::rareRessourceTypes.reserve (
      ressourcesJson["RareRessources"].size ());

  for (const auto &resData : ressourcesJson["RareRessources"])
    {
      ressources.try_emplace (resData.value ("Id", -1),
                              resData.value ("Name", "Unknown"),
                              resData.value ("Max_Quantity", -1));

      Ressource::rareRessourceTypes.push_back (resData.value ("Id", -1));
    }

  Ressource::craftableRessourceTypes.reserve (
      ressourcesJson["ManufacturedRessources"].size ());

  for (const auto &resData : ressourcesJson["ManufacturedRessources"])
    {
      ressources.try_emplace (resData.value ("Id", -1),
                              resData.value ("Name", "Unknown"),
                              resData.value ("Max_Quantity", -1));

      Ressource::craftableRessourceTypes.push_back (resData.value ("Id", -1));
    }
}

void
RessourceManager::gatherSand ()
{
  ressources[RessourcesAlias::SAND].add (1);
}

double
RessourceManager::getCurrentQuantity (RessourceType t)
{
  return ressources[t].getCurrentQuantity ();
}

double
RessourceManager::getMaxQuantity (RessourceType t)
{
  return ressources[t].getMaxQuantity ();
}

void
RessourceManager::add (RessourceType t, double n)
{
  ressources[t].add (n);
}

std::string_view
RessourceManager::getName (RessourceType r)
{
  return ressources[r].getName ();
}

void
RessourceManager::zerosValuePerTick ()
{
  for (auto &[_, res] : ressources)
    {
      res.resetValuesPerTick ();
    }
}

void
RessourceManager::addToProdPerTick (RessourceType t, double n)
{
  if (n < 0)
    {
      ressources[t].addToConsumptionPerTick (-n);
    }
  else
    {
      ressources[t].addToProdPerTick (n);
    }
}

double
RessourceManager::getNetProduction (RessourceType t)
{
  return ressources[t].getNetProduction ();
}

void
RessourceManager::consume (
    const std::unordered_map<RessourceType, double> &rates)
{
  for (const auto &[type, rate] : rates)
    {
      ressources[type].add (-rate);
      ressources[type].addToConsumptionPerTick (rate);
    }
}

void
RessourceManager::produce (
    const std::unordered_map<RessourceType, double> &rates)
{
  for (const auto &[type, rate] : rates)
    {
      ressources[type].add (rate);
      ressources[type].addToProdPerTick (rate);
    }
}

void
RessourceManager::tryConvert (
    const std::vector<std::pair<RessourceType, double> > &from,
    const std::vector<std::pair<RessourceType, double> > &to)
{
  bool canConvert = true;
  for (const auto &[rType, cons] : from)
    {
      if (cons > ressources[rType].getCurrentQuantity ())
        canConvert = false;
    }

  if (!canConvert)
    return;

  for (const auto &[rType, cons] : from)
    {
      ressources[rType].add (-cons);
      ressources[rType].addToConsumptionPerTick (cons);
    }

  for (const auto &[rType, prod] : to)
    {
      ressources[rType].add (prod);
      ressources[rType].addToProdPerTick (prod);
    }
}

std::vector<std::pair<RessourceType, double> >
RessourceManager::getData () const
{
  std::vector<std::pair<RessourceType, double> > result;
  for (const auto &[rtype, res] : ressources)
    {
      result.emplace_back (rtype, res.getCurrentQuantity ());
    }

  return result;
}

void
RessourceManager::loadData (
    const std::vector<std::pair<RessourceType, double> > &data)
{
  for (const auto &[rType, quant] : data)
    {
      ressources[rType].setQuantity (quant);
    }
}

double
RessourceManager::getProduction (RessourceType r)
{
  return ressources[r].getProduction ();
}

double
RessourceManager::getConsumption (RessourceType r)
{
  return ressources[r].getConsumption ();
}