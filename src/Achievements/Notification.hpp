#pragma once

#include "GameIDsTypes.hpp"
#include <string_view>

class Notification
{
public:
  explicit Notification (AchievementIDs);
  std::string_view getNotificationText () const;

private:
  std::string_view text;
};