#include "Notification.hpp"
#include "AchievementIDs.hpp"
#include <cassert>
#include <string_view>

Notification::Notification (AchievementIDs id)
{
  using enum AchievementIDs;
  switch (id)
    {
    case FirstJelly:
      text = "bjr";
      break;

    case RessourceFood:
      text = "foooood !";
      break;

    default:
      assert (false);
    }
}

std::string_view
Notification::getNotificationText () const
{
  return text;
}