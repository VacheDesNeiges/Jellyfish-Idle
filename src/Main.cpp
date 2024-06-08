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

// todolist ----------------
// Features :

// TODO : add production in the description of buildings hover
// TODO : add a cooldown to abilities ?
// TODO : Catchup on load
// TODO : add save and load to leveling system // Done for crafts, jobs to do
// TODO : add a keep crafting functionality
// TODO : display unlocked things by depth + incitation text to explore deeper
// on depth tab

// Polishing :

// TODO : unify the button size in a file.
// TODO : use different colors for xp bar and progress bar
// TODO : refactor the leveling system ?
// TODO : create one or multiples files containing all the global constants of
// the game
// TODO : Try using std::span on function that returns vectors ?

// Bugs :
// TODO : Savefile format stores enums with integers, making the saves prone to
// break when inserting a new value in enums. Needs a more robust solution
// TODO : parenthesis still display next to the price at the last second in
// button's hover
// TODO : remove time estimation when no ressource generation ?
// TODO : fix time estimation when ressource prod is <= 0 (time to zero)

// Roadmap :

// -> Slabs unlock stone shelves
// TESTS !!!!

// Future buildings :
// Marine Stockroom
// Oceanic Vault
// Abyssal Hoard
// Glassblower's Atelier
// Submerged Library

// Garden :
// Long time growing, harvest, allow auto harvest and auto repeat with
// achievements
// Plankton for food (lure in jellies)
// Oysters for pearls (insight related, consume sand and food)

// at some point, using std::map might end up causing performance issues, in
// this case, try boost's flat map, and then implement a short version of it
// (vector of pair, sort by first element which is an enum (try concepts),
// binary search for access, iterable)
