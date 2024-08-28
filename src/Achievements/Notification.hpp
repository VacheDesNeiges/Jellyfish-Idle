#pragma once

#include <string>

class Notification
{
  public:
    explicit Notification(std::string);
    std::string_view getNotificationText() const;

  private:
    std::string text;
};
