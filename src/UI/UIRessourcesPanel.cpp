#include "UIRessourcesPanel.hpp"

#include "GameIDsTypes.hpp"
#include "UIUtils.hpp"
#include "imgui.h"
#include "imgui_internal.h"

#include <cfloat>

void UIRessourcesPanel::render() const
{
    renderRessources();
    if (achievementsView()->isUnlocked(
            AchievementsAlias::ANYMANUFACTUREDRESSOURCE))
        renderManufacturedRessources();
}

void UIRessourcesPanel::renderRessources() const
{
    if (!ImGui::Begin("Ressources", nullptr, ImGuiWindowFlags_NoMove))
    {
        ImGui::End();
        return;
    }

    renderJfishNumbers();

    ImGui::SeparatorText("");

    setupColumns();
    for (const auto &ressource : ressourcesView()->getRegularRessourceTypes())
    {
        if (!achievementsView()->isUnlocked(ressource))
            continue;
        renderRessource(ressource, true);
    }
    ImGui::EndColumns();

    if (achievementsView()->isUnlocked(AchievementsAlias::ANYRARERESSOURCE))
    {
        ImGui::SeparatorText("Rare Ressources");
        setupColumns();
        for (const auto &rareRessource :
             ressourcesView()->getRareRessourceTypes())
        {
            if (!achievementsView()->isUnlocked(rareRessource))
                continue;
            renderRessource(rareRessource);
        }
        ImGui::EndColumns();
    }

    ImGui::End();
}

void UIRessourcesPanel::renderJfishNumbers() const
{

    ImGui::Text("Jellyfish");
    ImGui::SameLine();
    std::string jfishtxt = UIUtils::formatQuantity(
        jelliesView()->getNumJellies(), jelliesView()->getMaxNumJellies());

    auto x = (ImGui::GetCursorPosX() + ImGui::GetColumnWidth() -
              ImGui::CalcTextSize(jfishtxt.c_str()).x - ImGui::GetScrollX() -
              2 * ImGui::GetStyle().ItemSpacing.x);

    if (x > ImGui::GetCursorPosX())
        ImGui::SetCursorPosX(x);

    ImGui::Text("%s", jfishtxt.c_str());
}

void UIRessourcesPanel::renderManufacturedRessources() const
{
    if (!ImGui::Begin("Manufactured Ressources", nullptr,
                      ImGuiWindowFlags_NoMove))
    {
        ImGui::End();
        return;
    }

    setupColumns();
    for (const auto &ressource : ressourcesView()->getCraftableRessourceTypes())
    {
        if (!achievementsView()->isUnlocked(ressource))
            continue;
        renderRessource(ressource);
    }
    ImGui::EndColumns();

    ImGui::End();
}

void UIRessourcesPanel::renderRessource(RessourceType ressource,
                                        bool hasMaxQuantity) const
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() +
                         ImGui::GetStyle().ItemSpacing.x);
    ImGui::Text("%s", ressourcesView()->getRessourceName(ressource).data());

    ImGui::SameLine();
    ImGui::NextColumn();

    std::string quantityString;
    if (hasMaxQuantity)
    {
        quantityString = UIUtils::formatQuantity(
            ressourcesView()->getRessourceQuantity(ressource),
            ressourcesView()->getRessourceMaxQuantity(ressource));
    }
    else
    {
        quantityString = UIUtils::formatQuantity(
            ressourcesView()->getRessourceQuantity(ressource));
    }

    auto textWidth = ImGui::CalcTextSize(quantityString.c_str()).x;
    auto columnWidth =
        ImGui::GetColumnWidth() - ImGui::GetStyle().ItemSpacing.x;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + columnWidth - textWidth);
    ImGui::Text("%s", quantityString.c_str());

    ImGui::SameLine();
    ImGui::NextColumn();

    const auto production = ressourcesView()->getRessourceProduction(ressource);
    const auto consumption =
        ressourcesView()->getRessourceConsumption(ressource);
    std::string formatedProd =
        UIUtils::formatQuantity(2 * (production - consumption)) + "/sec";

    auto prodWidth = ImGui::CalcTextSize(formatedProd.c_str()).x;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + columnWidth - prodWidth - 5);
    ImGui::Text("%s", formatedProd.c_str());

    ImGui::NextColumn();
}

void UIRessourcesPanel::setupColumns() const
{
    ImGui::Columns(3, nullptr, false);
    ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() / 3);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() / 3);
    ImGui::SetColumnWidth(2, ImGui::GetWindowWidth() / 3);
}