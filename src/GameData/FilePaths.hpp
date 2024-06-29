#pragma once

#include <cassert>
#include <linux/limits.h>
#include <string>
#include <string_view>
#include <unistd.h>

namespace FilePaths
{

inline constexpr std::string_view FontPath = "/assets/font/OpenSans-Bold.ttf";
inline constexpr std::string_view RessourcesPath
    = "/assets/jsons/ressources.json";

inline std::string_view
getPath ()
{
  static std::string path;
  if (!path.empty ())
    return path;

  path.resize (PATH_MAX);

  ssize_t len = ::readlink ("/proc/self/exe\0", &path[0], PATH_MAX - 1);

  if (len != -1)
    {
      path.resize (static_cast<unsigned long> (len));
      std::size_t found = path.rfind ('/');
      if (found != std::string::npos)
        path.resize (found);
      return path;
    }
  assert (false);
}

}