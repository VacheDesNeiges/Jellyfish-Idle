#pragma once
#include <memory>
class GameDataView;

class GameDataAccess
{
public:
  static void bindDataView (std::shared_ptr<GameDataView>);

protected:
  std::shared_ptr<GameDataView> getDataView () const;

private:
  static inline std::shared_ptr<GameDataView> view = nullptr;
};