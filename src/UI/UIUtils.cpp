#include "UIUtils.hpp"
#include "RessourceDataView.hpp"
#include "fmt/core.h"
#include "imgui.h"
#include <cmath>

void UIUtils::setBaseUITheme()
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.SeparatorTextAlign = {0.5, 0.5};
    style.FrameRounding = 5.f;
    style.FramePadding = {20.f, 3.f};
    style.WindowRounding = 5.f;
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.TabBarBorderSize = 0;
    style.TabRounding = 0;

    ImVec4 *colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Border] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_Text] = UIColors::RegularText;

    colors[ImGuiCol_ModalWindowDimBg] = UIColors::Dimming;

    colors[ImGuiCol_WindowBg] = UIColors::FullyTransparent;
    colors[ImGuiCol_PopupBg] = UIColors::NotificationBG;

    colors[ImGuiCol_Button] = UIColors::Buttons;
    colors[ImGuiCol_ButtonHovered] = UIColors::HoveredElements;
    colors[ImGuiCol_ButtonActive] = UIColors::ActivatedElement;

    colors[ImGuiCol_TitleBg] = UIColors::FullyTransparent;
    colors[ImGuiCol_TitleBgActive] = UIColors::FullyTransparent;
    colors[ImGuiCol_Separator] = UIColors::UnfocusedTransparentElement;

    colors[ImGuiCol_FrameBg] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_PlotHistogram] = UIColors::ActivatedTransparentElement;

    colors[ImGuiCol_TitleBgActive] = UIColors::FullyTransparent;

    colors[ImGuiCol_TabUnfocused] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_TabUnfocusedActive] = UIColors::ActivatedTransparentElement;

    colors[ImGuiCol_TabActive] = UIColors::ActivatedTransparentElement;

    colors[ImGuiCol_Tab] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_TabHovered] = UIColors::ActivatedElement;

    colors[ImGuiCol_HeaderHovered] = UIColors::Buttons;
    colors[ImGuiCol_HeaderActive] = UIColors::Buttons;

    colors[ImGuiCol_TableHeaderBg] = UIColors::Buttons;
    colors[ImGuiCol_TableBorderLight] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_TableBorderStrong] = UIColors::UnfocusedTransparentElement;
    colors[ImGuiCol_TableRowBg] = UIColors::FullyTransparent;
    colors[ImGuiCol_TableRowBgAlt] = UIColors::Dimming;
}

void UIUtils::printCostsImGui(
    std::shared_ptr<const RessourceDataView> rView,
    const std::vector<std::pair<RessourceType, double>> &ressourcesCost)

{
    if (ressourcesCost.empty())
        return;

    ImVec4 textColor;

    for (const auto &[ressource, cost] : ressourcesCost)
    {
        auto currentQuantity = rView->getRessourceQuantity(ressource);
        auto ressourceName = rView->getRessourceName(ressource);
        std::string formatedResourceQuant;
        std::string formatedTime;
        if (cost > rView->getRessourceMaxQuantity(ressource))
        {
            textColor = UIColors::ErrorText;
        }
        else if (cost <= currentQuantity)
        {
            textColor = UIColors::ValidText;
        }
        else
        {
            textColor = UIColors::GreyedText;
            auto prodPerSec = (rView->getRessourceProduction(ressource) -
                               rView->getRessourceConsumption(ressource)) *
                              2;

            formatedTime =
                formatRemainingTime(currentQuantity, cost, prodPerSec);
        }

        formatedResourceQuant = fmt::format(
            "{} : {}", ressourceName, formatQuantity(currentQuantity, cost));

        if (!formatedTime.empty())
            formatedResourceQuant += (" (" + formatedTime + ')');

        ImGui::TextColored(textColor, "%s", formatedResourceQuant.c_str());
    }
}

std::string UIUtils::formatQuantity(double quantity)
{
    auto ret = fmt::format("{:.3f}", quantity);
    ret.erase(ret.find_last_not_of('0') + 1, ret.size());
    if (ret.back() == '.')
        ret.pop_back();

    return ret;
}

std::string UIUtils::formatQuantity(double quantity, double maxQuantity)
{
    return fmt::format("{}/{}", formatQuantity(quantity),
                       formatQuantity(maxQuantity));
}

std::string UIUtils::formatRemainingTime(double currentQuantity, double target,
                                         double progressionRate)
{
    if (progressionRate <= 0)
        return "";

    double missingRessources = target - currentQuantity;
    double secondsUntilTargetMet = missingRessources / progressionRate;

    auto hours = std::floor(secondsUntilTargetMet / 3600);
    secondsUntilTargetMet -= (3600 * hours);
    auto minutes = std::floor(secondsUntilTargetMet / 60);
    secondsUntilTargetMet -= (60 * minutes);
    auto seconds = std::floor(secondsUntilTargetMet);

    std::string formatedString;
    if (hours > 0)
        formatedString += fmt::format("{} hours", hours);
    if (minutes > 0)
    {
        if (!formatedString.empty())
            formatedString += " ";
        formatedString += fmt::format("{} minutes", minutes);
    }
    if (seconds > 0 || !formatedString.empty())
    {
        if (!formatedString.empty())
            formatedString += " ";
        formatedString += fmt::format("{} seconds", std::floor(seconds));
    }

    return formatedString;
}
