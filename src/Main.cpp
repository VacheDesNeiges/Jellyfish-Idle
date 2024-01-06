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
