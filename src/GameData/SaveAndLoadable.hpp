#pragma once

/**
 * @brief An abstract class that enforces the implementation of save and load
 * functions
 *
 * @tparam T The type of the data chosen to be loaded or serialized
 */

template <typename T> class SaveAndLoadable
{
  public:
    virtual void loadData(const T &) = 0;
    virtual T getData() const = 0;
};
