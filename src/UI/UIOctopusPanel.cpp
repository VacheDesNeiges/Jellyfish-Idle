#include "UIOctopusPanel.hpp"

#include "GameIDsTypes.hpp"
#include "UIUtils.hpp"
#include "fmt/core.h"
#include "imgui.h"

void UIOctopusPanel::render() const
{
    if (!ImGui::Begin("Octopus", nullptr,
                      ImGuiWindowFlags_NoMove &
                          ImGuiWindowFlags_NoFocusOnAppearing))
    {
        ImGui::End();
        return;
    }

    static bool showBoughtUpgrades = false;
    ImGui::Checkbox("Show bought upgrades", &showBoughtUpgrades);

    for (const auto &upgradeID : upgradeView()->getUpgradesTypes())
    {
        if (showBoughtUpgrades)
        {
            if (upgradeView()->isBought(upgradeID))
                renderTradeButton(upgradeID);
        }
        else
        {
            if (upgradeView()->isAvailableForBuying(upgradeID))

                renderTradeButton(upgradeID);
        }
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 80);
    renderQuestCard();

    ImGui::End();
}

void UIOctopusPanel::renderTradeButton(UpgradeID id) const
{
    auto size = ImVec2(300.f, 45.f);

    ImGui::BeginDisabled(!upgradeView()->isBuyable(id));

    if (std::string buttonText =
            fmt::format("{}\n", upgradeView()->getName(id));
        ImGui::Button(buttonText.c_str(), size))
    {
        inputHandler->buy(id);
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone |
                             ImGuiHoveredFlags_AllowWhenDisabled) &&
        ImGui::BeginTooltip())
    {
        std::string tooltipText =
            fmt::format("{}", upgradeView()->getDescription(id));
        ImGui::Text("%s", tooltipText.c_str());

        auto cost = upgradeView()->getCost(id);
        UIUtils::printCostsImGui(ressourcesView(), cost);

        ImGui::EndTooltip();
    }

    ImGui::EndDisabled();
}

void UIOctopusPanel::renderQuestCard() const
{
    const ImVec2 size{400, 0};
    ImGui::PushStyleColor(ImGuiCol_ChildBg, UIColors::CardElements);
    ImGui::BeginChild("##", size, ImGuiChildFlags_AutoResizeY);
    ImGui::SeparatorText("Octopus Request");
    ImGui::TextWrapped(
        "%s",
        questsView()->getCurrentQuestText(QuestLineEnum::Octopus).c_str());

    ImGui::SeparatorText("Ressources Requested");
    UIUtils::printCostsImGui(
        ressourcesView(),
        questsView()->getCurrentQuestRequirements(QuestLineEnum::Octopus));

    if (ImGui::Button("Give Ressources"))
    {
        inputHandler->completeQuest(QuestLineEnum::Octopus);
    }
    ImGui::NewLine();

    ImGui::EndChild();
    ImGui::PopStyleColor();
}
