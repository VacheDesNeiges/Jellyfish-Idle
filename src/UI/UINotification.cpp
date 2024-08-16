#include "UINotification.hpp"
#include "imgui.h"

void UINotification::render() const
{
    if (auto notif = achievementsView()->getNextNotification();
        notif.has_value())
    {
        ImGui::OpenPopup("Notifications");
        ImGui::SetNextWindowSize({400, 0});

        if (ImGui::BeginPopupModal("Notifications", nullptr,
                                   ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoMove))
        {
            ImGui::TextWrapped("%s", std::string(notif.value()).c_str());

            if (ImGui::Button("close"))
            {
                inputHandler->removeCurrentNotification();
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
}
