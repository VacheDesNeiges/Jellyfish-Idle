#include "Game.hpp"
#include <memory>

int
main ()
{
  auto g = std::make_unique<Game> ();
  g->run ();

  return 0;
}

// TODO : implement manufacturing job
// TODO : implement new octopus upgrades (canalizing and writing)
// TODO : add a cooldown to abilities;
// TODO : Catchup on load
// TODO : unify the button size in a file. Maybe rename UIColors.hpp to
// UISettings.hpp and create another namespace there
// TODO : remove octopus upgrades once bought and display their price
// TODO : add an option to see octopus upgrade that are already bought (greyed)
