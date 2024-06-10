#pragma once

#include "GameDataView.hpp"
#include "imgui.h"

#include <memory>

namespace UIColors
{
constexpr ImVec4 redText (1, 0, 0, 1);
constexpr ImVec4 greyText (0.8f, 0.8f, 0.8f, 1);
constexpr ImVec4 greenText (0, 1, 0, 1);

}

namespace UIUtils
{

void printCostsImGui (
    std::shared_ptr<GameDataView> gData,
    const std::vector<std::pair<RessourceType, double> > &ressourcesNeeded);
}

namespace UIConstants
{
constexpr auto UIBuildingButtonSize = ImVec2{ 300.f, 45.f };
}