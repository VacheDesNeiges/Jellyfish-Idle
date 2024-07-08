#pragma once

#include "GameIDsTypes.hpp"

class Jellyfish
{
public:
  void setJob (JellyJob);
  void gainJobExp (unsigned);
  JellyJob getJob () const;

private:
  JellyJob currentJob = JobsAlias::NONE;
};