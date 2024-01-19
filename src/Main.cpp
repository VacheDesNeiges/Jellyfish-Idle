#include "Game.hpp"

#include <memory>

int
main ()
{
  auto g = std::make_unique<Game> ();
  g->run ();

  return 0;
}

// todolist ----------------
// Features :

// TODO : implement manufacturing job
// TODO : implement new octopus upgrades (canalizing and writing)
// TODO : add a cooldown to abilities;
// TODO : Catchup on load
// TODO : add save and load function to crafting system

// Polishing :

// TODO : unify the button size in a file.
// TODO : grey out upgrades once they are bought (when displayed optionaly)
// TODO : use different colors for xp bar and progress bar
// TODO : Try using columns for buildings and jobs ui rendering

// Bugs :
// TODO : Savefile format stores enums with integers, making the saves prone to
// break when inserting a new value in an enum. Needs a more robust solution

// Roadmap :

// Crafting System -> Leveling System -> Tests

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

// at some point, using std::map might end up causing performance issues, in
// this case, try boost's flat map, and then implement a short version of it
// (vector of pair, sort by first element which is an enum (try concepts),
// binary search for access, iterable)