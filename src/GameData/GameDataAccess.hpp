#pragma once
#include <memory>
class GameDataView;

class GameDataAcess
{
public:
  void bindDataView (std::shared_ptr<GameDataView>);

protected:
  std::shared_ptr<GameDataView> getDataView () const;

private:
  std::shared_ptr<GameDataView> view = nullptr;
};