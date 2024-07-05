#include "Notification.hpp"
#include <cassert>
#include <string_view>

Notification::Notification (AchievementIDs id)
{
  switch (static_cast<int> (id))
    {
    case 1: // FIXME add notification text in achievements (std optional)
      text = "You lured your first jellyfish. You can now assign it a job in "
             "the job tab. For now, you can only choose to explore the sea, "
             "maybe you'll find something interesting!";
      break;

    case 2:
      text = "With time, your jellies assigned to exploring will discover "
             "many useful things that will help your progression. You can see "
             "what they have found so far in the depth tab";
      break;

    default:
      text = "Wiiii";
    }
}

std::string_view
Notification::getNotificationText () const
{
  return text;
}