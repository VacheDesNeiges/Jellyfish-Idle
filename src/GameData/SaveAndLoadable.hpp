#pragma once

/**
 * @brief An interface that enforces the implementation of save and load
 * functions
 *
 * @tparam T The type of the data chosen to be loaded or serialized
 */

template <typename T> class SaveAndLoadable
{
  public:
    virtual ~SaveAndLoadable() = default;
    virtual void loadData(const T &) = 0;
    virtual T getData() const = 0;
};
