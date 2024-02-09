#include "Game.hpp"

#include <memory>
#include <optional>

int
main (int argc, char *argv[])
{
  std::optional<std::string_view> option;
  if (argc == 2)
    option = argv[1];

  auto g = std::make_unique<Game> ();
  g->run (option);

  return 0;
}

// todolist ----------------
// Features :

// TODO : add production in the description of buildings hover
// TODO : add a little descriptive text in the decription of building hover
// TODO : add a cooldown to abilities ?
// TODO : Catchup on load
// TODO : add save and load function to crafting system
// TODO : add save and load to leveling system
// TODO : add a keep crafting functionality

// Polishing :

// TODO : unify the button size in a file.
// TODO : use different colors for xp bar and progress bar
// TODO : gate levels behind achievements
// TODO : refactor the leveling system ?
// TODO : create one or multiples files containing all the global constants of
// the game

// Bugs :
// TODO : Savefile format stores enums with integers, making the saves prone to
// break when inserting a new value in enums. Needs a more robust solution
// TODO : stop exp being attributed when no recipes are ongoing

// Roadmap :

// Crafting System -> Leveling System -> Tests

// Telekinesis upgrade for insight
// -> Unlocks Mining job
// Advanced Telekinesis
// -> unlocks manufacturing job with stone Slabs. Slabs have a stock
// limit ?
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