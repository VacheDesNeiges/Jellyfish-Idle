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
// TODO : take care of negative ressources
// TODO : Catchup on load
// TODO : Replace string returns to string_view
// TODO : QoL consumption/production per sec next to ressources numbers
