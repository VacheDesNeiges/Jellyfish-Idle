#include "Game.hpp"

#include <optional>

int
main (int argc, char *argv[])
{
  std::optional<std::string_view> option;
  if (argc == 2)
    option = argv[1];

  Game g;
  g.run (option);
}
