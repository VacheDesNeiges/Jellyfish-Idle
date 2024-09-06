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
constexpr ImVec4 GreyedText(0.8F, 0.8F, 0.8F, 1);
constexpr ImVec4 ValidText(0, 1, 0, 1);

// UI Elements Colors
//-------------------------------------------------
constexpr ImVec4 FullyTransparent(0, 0, 0, 0);
constexpr ImVec4 Buttons(0.069F, 0.071F, 0.109F, 1.000F);

constexpr ImVec4 CardElements(0, 0, 0, 0.7F);

constexpr ImVec4 HoveredElements(0.642F, 0.000F, 0.116F, 1.000F);
constexpr ImVec4 ActivatedElement(0.896F, 0.000F, 0.162F, 1.000F);

constexpr ImVec4 ActivatedTransparentElement(0.796F, 0.039F, 0.176F, 0.494F);
constexpr ImVec4 UnfocusedTransparentElement(0.134F, 0.000F, 0.000F, 0.826F);

constexpr ImVec4 Dimming(0.174F, 0.085F, 0.117F, 0.478F);
constexpr ImVec4 NotificationBG(0.132F, 0.132F, 0.209F, 1.000F);
} // namespace UIColors

namespace UIConstants
{
constexpr auto UIBuildingButtonSize = ImVec2{300.F, 35.F};
constexpr auto UITooltipSize = ImVec2{300, -1};
} // namespace UIConstants

namespace UIUtils
{

void setBaseUITheme();

void printCostsImGui(
    std::shared_ptr<const RessourceDataView> rView,
    const std::vector<std::pair<RessourceType, double>> &ressourcesCost);

std::string formatQuantity(double quantity);
std::string formatQuantity(double quantity, double maxQuantity);
std::string formatRemainingTime(double currentQuantity, double target,
                                double progressionRate);

} // namespace UIUtils
