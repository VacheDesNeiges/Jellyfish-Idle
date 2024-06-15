#include "Notification.hpp"
#include <string_view>

std::string_view
Notification::getNotificationText () const
{
  return text;
}