#include "GameDataAccess.hpp"
#include "GameDataView.hpp"
#include <cassert>
#include <memory>

void
GameDataAcess::init (std::shared_ptr<GameDataView> v)
{
  assert (view == nullptr);
  view = v;
}

std::shared_ptr<GameDataView>
GameDataAcess::getDataView () const
{
  assert (view != nullptr);
  return view;
}