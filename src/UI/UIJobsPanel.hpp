#pragma once
#include "Jellyfish.hpp"
#include "UIElement.hpp"

class UIJobsPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderJobsControls (JellyJobs) const;
};