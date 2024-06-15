#pragma once

#include <string_view>

class Notification
{
public:
  std::string_view getNotificationText () const;

private:
  const std::string_view text;
};