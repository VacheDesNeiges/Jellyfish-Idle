#include "UIBuildingsPanel.hpp"

#include "GameIDsTypes.hpp"
#include "UIUtils.hpp"

#include "imgui.h"
#include <fmt/core.h>
#include <fmt/format.h>

void UIBuildingPanel::render() const
{
    if (!ImGui::Begin("Buildings", nullptr,
                      ImGuiWindowFlags_NoMove |
                          ImGuiWindowFlags_NoFocusOnAppearing))
    {
        ImGui::End();
        return;
    }

    ImGui::SetCursorPosX(50);
    ImGui::SetCursorPosY(40);

    if (ImGui::Button("Gather Sand", UIConstants::UIBuildingButtonSize))
    {
        inputHandler->gatherSand();
    }

    bool odd = !renderJellyfishLuringButton();
    if (!odd)
        ImGui::SetCursorPosX(50);

    for (const auto &building : buildingsView()->getBuildingTypes())
    {
        if (renderBuildingButton(building))
        {
            odd = !odd;
            ImGui::SetCursorPosX(50);
        }

        if (odd)
            ImGui::SameLine();
    }
    ImGui::End();
}

bool UIBuildingPanel::renderBuildingButton(BuildingType building) const
{

    if (achievementsView()->isUnlocked(building))
    {
        ImGui::BeginDisabled(!buildingsView()->isBuyable(building));
        auto name = buildingsView()->getBuildingName(building);
        auto quantity = buildingsView()->getBuildingQuantity(building);

        if (std::string buttonText = fmt::format("{} lvl {}", name, quantity);
            ImGui::Button(buttonText.c_str(),
                          UIConstants::UIBuildingButtonSize))
        {
            inputHandler->buy(building);
        }
        ImGui::EndDisabled();
        setToolTip(building);

        return true;
    }
    return false;
}

void UIBuildingPanel::setToolTip(BuildingType building) const
{
    ImGui::PushStyleColor(ImGuiCol_Separator,
                          ImVec4(0.766f, 0.720f, 0.741f, 0.224f));
    ImGui::SetNextWindowSize({300, -1});

    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone |
                             ImGuiHoveredFlags_AllowWhenDisabled) &&
        ImGui::BeginTooltip())
    {

        ImGui::SeparatorText("Description");
        ImGui::TextWrapped(
            "%s\n", buildingsView()->getBuildingDescription(building).c_str());

        auto ressourcesNeeded = buildingsView()->getNextBuyCost(building);
        ImGui::SeparatorText("Price");
        UIUtils::printCostsImGui(ressourcesView(), ressourcesNeeded);

        ImGui::EndTooltip();
    }
    ImGui::PopStyleColor();
}

bool UIBuildingPanel::renderJellyfishLuringButton() const
{
    ImGui::SameLine();

    if (achievementsView()->isUnlocked(AchievementsAlias::JELLYFISHLURING))
    {
        ImGui::BeginDisabled(!jelliesView()->canLure());

        if (ImGui::Button("Lure Jellyfish", UIConstants::UIBuildingButtonSize))
        {
            inputHandler->lureJellyfish();
        }
        ImGui::EndDisabled();
        ImGui::SetNextWindowSize({300, -1});

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone |
                                 ImGuiHoveredFlags_AllowWhenDisabled) &&
            ImGui::BeginTooltip())
        {
            ImGui::TextWrapped(
                "Allows you to use some food to lure a jellyfish");

            if (jelliesView()->getMaxNumJellies() ==
                jelliesView()->getNumJellies())
            {
                ImGui::PushStyleColor(ImGuiCol_Text, UIColors::ErrorText);
                ImGui::TextWrapped("Not enough room to host more jellies");
                ImGui::PopStyleColor();
            }

            ImGui::SeparatorText("Price :");
            UIUtils::printCostsImGui(ressourcesView(),
                                     {jelliesView()->getLureCost()});

            ImGui::EndTooltip();
        }

        return true;
    }
    return false;
}
