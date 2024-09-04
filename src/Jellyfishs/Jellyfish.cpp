#include "Jellyfish.hpp"
#include "GameIDsTypes.hpp"

JellyJob Jellyfish::getJob() const
{
    return currentJob;
}

void Jellyfish::setJob(JellyJob jJob)
{
    currentJob = jJob;
}
