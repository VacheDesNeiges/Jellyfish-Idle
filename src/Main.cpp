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
// TODO : unify the button size in a file.
// TODO : add a time estimation for buyables tooltips
// TODO : grey out upgrades once they are bought (when displayed optionaly)