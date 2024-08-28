#pragma once

#include "RessourceDataView.hpp"
#include "imgui.h"

#include <SDL2/SDL_render.h>
#include <memory>

namespace UIColors
{

// Text Colors
//-------------------------------------------------
constexpr ImVec4 RegularText(1, 1, 1, 1);
constexpr ImVec4 ErrorText(1, 0, 0, 1);
constexpr ImVec4 GreyedText(0.8f, 0.8F, 0.8F, 1);
constexpr ImVec4 ValidText(0, 1, 0, 1);

// UI Elements Colors
//-------------------------------------------------
constexpr ImVec4 FullyTransparent(0, 0, 0, 0);
constexpr ImVec4 Buttons(0.069f, 0.071f, 0.109f, 1.000f);

constexpr ImVec4 CardElements(0, 0, 0, 0.7f);

constexpr ImVec4 HoveredElements(0.642f, 0.000f, 0.116f, 1.000f);
constexpr ImVec4 ActivatedElement(0.896f, 0.000f, 0.162f, 1.000f);

constexpr ImVec4 ActivatedTransparentElement(0.796f, 0.039f, 0.176f, 0.494f);
constexpr ImVec4 UnfocusedTransparentElement(0.134f, 0.000f, 0.000f, 0.826f);

constexpr ImVec4 Dimming(0.174f, 0.085f, 0.117f, 0.478f);
constexpr ImVec4 NotificationBG(0.132f, 0.132f, 0.209f, 1.000f);
} // namespace UIColors

namespace UIConstants
{
constexpr auto UIBuildingButtonSize = ImVec2{300.f, 35.f};
constexpr auto UITooltipSize = ImVec2{300, -1};
} // namespace UIConstants

namespace UIUtils
{

void setBaseUITheme();

void printCostsImGui(
    std::shared_ptr<const RessourceDataView> gData,
    const std::vector<std::pair<RessourceType, double>> &ressourcesNeeded);

std::string formatQuantity(double quantity);
std::string formatQuantity(double quantity, double maxQuantity);
std::string formatRemainingTime(double currentQuantity, double target,
                                double progressionRate);

} // namespace UIUtils
