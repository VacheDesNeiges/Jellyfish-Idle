#include "Jellyfish.hpp"

JellyJobs
Jellyfish::getJob () const
{
  return currentJob;
}

void
Jellyfish::setJob (JellyJobs j)
{
  currentJob = j;
}