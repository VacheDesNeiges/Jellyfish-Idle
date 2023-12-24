#include "GameDataAccess.hpp"
#include "GameDataView.hpp"
#include <cassert>
#include <iostream>
#include <memory>

void
GameDataAccess::bindDataView (std::shared_ptr<GameDataView> v)
{
  assert (view == nullptr);
  view = v;
  std::cout << "call to bind data view\n";
}

std::shared_ptr<GameDataView>
GameDataAccess::getDataView () const
{
  assert (view != nullptr);
  return view;
}