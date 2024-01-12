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
// TODO : grey out upgrades once they are bought (when displayed optionaly)

// at some point, using std::map might end up causing performance issues, in
// this case, try boost's flat map, and then implement a short version of it
// (vector of pair, sort by first element which is an enum (try concepts),
// binary search for access, iterable)

// ROADMAP :
// Telekinesis upgrade for insight
// -> Unlocks Mining job
// Advanced Telekinesis
// -> unlocks manufacturing job with stone Slabs. Slabs have a stock
// limit
// -> Slabs unlock stone shelves
// TESTS !!!!

// Future buildings :
// Marine Stockroom
// Oceanic Vault
// Abyssal Hoard