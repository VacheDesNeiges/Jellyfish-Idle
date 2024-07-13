#include "RessourceManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <cmath>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

RessourceManager::RessourceManager () { init (); }

void
RessourceManager::init ()
{
  auto fstream = FilePaths::getFileStream (FilePaths::RessourcesPath);

  try
    {
      nlohmann::json ressourcesJson = nlohmann::json::parse (fstream);

      ressources.reserve (
          ressourcesJson.at ("Ressources").size ()
          + ressourcesJson.at ("RareRessources").size ()
          + ressourcesJson.at ("ManufacturedRessources").size ());

      regularRessourceTypes.reserve (ressourcesJson.at ("Ressources").size ());
      for (const auto &resData : ressourcesJson["Ressources"])
        {
          ressources.try_emplace (RessourceType (resData.at ("Id")), resData);
          regularRessourceTypes.push_back (RessourceType (resData.at ("Id")));
        }

      rareRessourceTypes.reserve (ressourcesJson["RareRessources"].size ());
      for (const auto &resData : ressourcesJson["RareRessources"])
        {
          ressources.try_emplace (RessourceType (resData.at ("Id")), resData);
          rareRessourceTypes.push_back (RessourceType (resData.at ("Id")));
        }

      craftableRessourceTypes.reserve (
          ressourcesJson["ManufacturedRessources"].size ());
      for (const auto &resData : ressourcesJson["ManufacturedRessources"])
        {
          ressources.try_emplace (RessourceType (resData.at ("Id")), resData);

          craftableRessourceTypes.push_back (
              RessourceType (resData.at ("Id")));
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing ressources :\n" << e.what () << "\n";
      abort ();
    }
  allRessourceTypes.reserve (regularRessourceTypes.size ()
                             + rareRessourceTypes.size ()
                             + craftableRessourceTypes.size ());

  allRessourceTypes.insert (allRessourceTypes.end (),
                            regularRessourceTypes.begin (),
                            regularRessourceTypes.end ());

  allRessourceTypes.insert (allRessourceTypes.end (),
                            rareRessourceTypes.begin (),
                            rareRessourceTypes.end ());

  allRessourceTypes.insert (allRessourceTypes.end (),
                            craftableRessourceTypes.begin (),
                            craftableRessourceTypes.end ());
}

void
RessourceManager::gatherSand ()
{
  ressources[RessourcesAlias::SAND].add (1);
}

double
RessourceManager::getCurrentQuantity (RessourceType t) const
{
  return ressources.at (t).getCurrentQuantity ();
}

double
RessourceManager::getMaxQuantity (RessourceType t) const
{
  return ressources.at (t).getMaxQuantity ();
}

void
RessourceManager::add (RessourceType t, double n)
{
  ressources[t].add (n);
}

std::string_view
RessourceManager::getName (RessourceType t) const
{
  return ressources.at (t).getName ();
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
RessourceManager::getNetProduction (RessourceType t) const
{
  return ressources.at (t).getNetProduction ();
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
RessourceManager::getProduction (RessourceType t) const
{
  return ressources.at (t).getProduction ();
}

double
RessourceManager::getConsumption (RessourceType t) const
{
  return ressources.at (t).getConsumption ();
}

std::span<const RessourceType>
RessourceManager::getAllRessourceTypes () const
{
  return std::span (allRessourceTypes);
}

std::span<const RessourceType>
RessourceManager::getRegularRessourceTypes () const
{
  return std::span (regularRessourceTypes);
}

std::span<const RessourceType>
RessourceManager::getRareRessourceTypes () const
{
  return std::span (rareRessourceTypes);
}
std::span<const RessourceType>
RessourceManager::getCraftableRessourceTypes () const
{
  return std::span (craftableRessourceTypes);
}

void
RessourceManager::updateMaxRessourcesQuantities (
    const std::unordered_map<RessourceType, double> &newQuantities)
{
  for (const auto &[rType, quant] : newQuantities)
    {
      ressources.at (rType).setBonusMaxQuantity (quant);
    }
}

void
RessourceManager::recomputeMaxQuantities ()
{
  std::unordered_map<RessourceType, double> newQuantities;
  for (const auto b : buildingsView ()->getBuildingTypes ())
    {
      for (const auto &[rType, quant] :
           buildingsView ()->getIncreasedStorage (b))
        {

          newQuantities[rType] += quant;
        }
    }
  updateMaxRessourcesQuantities (newQuantities);
}