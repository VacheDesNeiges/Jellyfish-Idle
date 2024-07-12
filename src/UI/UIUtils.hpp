#pragma once

#include "GameDataView.hpp"
#include "imgui.h"

#include <memory>

namespace UIColors
{
constexpr ImVec4 errorText (1, 0, 0, 1);
constexpr ImVec4 greyedText (0.8f, 0.8f, 0.8f, 1);
constexpr ImVec4 validText (0, 1, 0, 1);

}

namespace UIConstants
{
constexpr auto UIBuildingButtonSize = ImVec2{ 300.f, 35.f };
}

namespace UIUtils
{

void printCostsImGui (
    std::shared_ptr<GameDataView> gData,
    const std::vector<std::pair<RessourceType, double> > &ressourcesNeeded);
}
