#include "Achievement.hpp"

bool
Achievement::isUnlocked () const
{
  return unlocked;
}

void
Achievement::unlock ()
{
  unlocked = true;
}