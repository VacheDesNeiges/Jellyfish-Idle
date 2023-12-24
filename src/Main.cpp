#include "Game.hpp"
#include <memory>

int
main ()
{
  auto g = std::make_unique<Game> ();
  g->run ();

  return 0;
}

// TODO : take care of negative ressources
// TODO : Catchup on load
// TODO : Replace string returns to string_view
// TODO : QoL consumption/production per sec next to ressources numbers
