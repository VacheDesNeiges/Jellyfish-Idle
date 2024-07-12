#include "UINotification.hpp"
#include "imgui.h"

void
UINotification::render () const
{
  if (auto notif = gData->getAchievementsView ()->getNextNotification ();
      notif.has_value ())
    {

      ImGui::SetNextWindowSize ({ 400, 250 });

      ImGui::OpenPopup ("Notification");
      if (ImGui::BeginPopupModal (
              "Notification", nullptr,
              ImGuiWindowFlags_NoMove
                  & ImGuiWindowFlags_NoBringToFrontOnFocus))
        {
          ImGui::TextWrapped ("%s", std::string (notif.value ()).c_str ());

          if (ImGui::Button ("close"))
            {
              inputHandler->removeCurrentNotification ();
              ImGui::CloseCurrentPopup ();
            }

          ImGui::EndPopup ();
        }
    }
}