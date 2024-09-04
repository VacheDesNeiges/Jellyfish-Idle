#include "Game.hpp"

#include <cstddef>
#include <optional>

int main(int argc, char *argv[])
{
    std::optional<std::string_view> option;
    if (argc > 1)
    {
        auto args = std::span(argv, size_t(argc));
        option = args[1];
    }

    Game game;
    game.run(option);
}
