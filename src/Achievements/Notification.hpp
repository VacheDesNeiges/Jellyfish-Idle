#pragma once

#include <string>

class Notification
{
  public:
    explicit Notification(const std::string &);
    std::string_view getNotificationText() const;

  private:
    std::string text;
};