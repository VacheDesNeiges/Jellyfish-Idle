#include "UINotification.hpp"
#include "imgui.h"

void
UINotification::render () const
{
  if (auto notif = gData->getAchievementsView ()->getNextNotification ();
      notif.has_value ())
    {
      ImGui::OpenPopup ("Notification");
      if (ImGui::BeginPopup ("Notification"))
        {
          ImGui::Text ("%s", std::string (notif.value ()).c_str ());
          ImGui::EndPopup ();
        }
      else
        {
          inputHandler->removeCurrentNotification ();
        }
    }
}