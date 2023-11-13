#include "Game.hpp"
#include <memory>

int
main ()
{
  auto g = std::make_unique<Game> ();
  g->run ();

  return 0;
}

// TODO : Catchup on load
// TODO : Replace string returns to string_view
// TODO : Insight Tab
// TODO : QoL consumption/production per sec next to ressources numbers
// TODO : QoL better description of buildings
// TODO : Gate other tabs behind achievements
// TODO : Gate Ressources numbers behind achievements
// TODO : Think about refactoring the GameDataSynchronizer class into multiple
// more specialized classes. they may need to hold a shared ptr to the
// managers.