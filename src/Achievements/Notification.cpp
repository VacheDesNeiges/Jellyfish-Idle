#include "Notification.hpp"
#include <cassert>
#include <string_view>

Notification::Notification(std::string str) : text(std::move(str))
{
}

std::string_view Notification::getNotificationText() const
{
    return text;
}
