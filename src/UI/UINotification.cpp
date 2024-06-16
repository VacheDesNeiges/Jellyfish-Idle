#include "UINotification.hpp"
#include "imgui.h"

void
UINotification::render () const
{
  if (auto notif = gData->getAchievementsView ()->getNextNotification ();
      notif.has_value ())
    {
      ImGui::Begin ("Notification", nullptr, ImGuiWindowFlags_None);
      ImGui::SetWindowFocus ();
      ImGui::Text ("%s", std::string (notif.value ()).c_str ());
      if (ImGui::Button ("close"))
        inputHandler->removeCurrentNotification ();
      ImGui::End ();
    }
}