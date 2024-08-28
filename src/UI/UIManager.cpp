#include "UIManager.hpp"
#include "GameIDsTypes.hpp"
#include "GameSystems.hpp"
#include "TextureAtlas.hpp"
#include "imgui.h"

#include <SDL2/SDL_render.h>
#include <fmt/core.h>
#include <memory>

void UIManager::bindInputHandler(const std::shared_ptr<InputHandler> &inputPtr)
{
    inputHandler = inputPtr;

    ressourcesPanel.bindInputHandler(inputPtr);
    buildingsPanel.bindInputHandler(inputPtr);
    jobsPanel.bindInputHandler(inputPtr);
    abilitiesPanel.bindInputHandler(inputPtr);
    depthPanel.bindInputHandler(inputPtr);
    octopusPanel.bindInputHandler(inputPtr);
    gardenPanel.bindInputHandler(inputPtr);
    notifications.bindInputHandler(inputPtr);
}

void UIManager::renderUI() const
{
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    buildingsPanel.render();

    using namespace AchievementsAlias;
    if (achievementsView()->isUnlocked(JOBSYSTEM))
        jobsPanel.render();

    if (achievementsView()->isUnlocked(ABILITYSYSTEM))
        abilitiesPanel.render();

    if (achievementsView()->isUnlocked(DEPTHSYSTEM))
        depthPanel.render();

    if (achievementsView()->isUnlocked(OCTOPUS))
        octopusPanel.render();

    if (achievementsView()->isUnlocked(GARDENSYSTEM))
        gardenPanel.render();

    ressourcesPanel.render();
    ImGui::ShowDemoWindow();
    ImGui::ShowStyleEditor();
    notifications.render();
}

void UIManager::setAtlas(TextureAtlas t)
{
    atlas = std::move(t);
    jobsPanel.loopButtonTexture = atlas.loopButton;
}
