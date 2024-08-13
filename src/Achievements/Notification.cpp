#include "Notification.hpp"
#include <cassert>
#include <string_view>

Notification::Notification(const std::string &str) : text(str)
{
}

std::string_view Notification::getNotificationText() const
{
    return text;
}