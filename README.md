# Jellyfish-Idle - A jellyfish themed incremental game
![CI](https://github.com/VacheDesNeiges/Jellyfish-Idle/actions/workflows/cmake-single-platform.yml/badge.svg)

This repository contains a work-in-progress jellyfish themed incremental game

![Screenshot](https://github.com/VacheDesNeiges/Jellyfish-Idle/blob/main/assets/jfishGame.png)



# Dependencies
This program requires the following tools and libraries :

- C++ 20 compiler
- CMake 3.22+
- Ninja

- STL
- SDL2
- fmt
- gtest
- nlohmann (json)


# Installation
Make sure that you have installed the required dependencies, then run the command
```
./build.sh --game
```

You may also build in debug mode by adding the arg --debug
```
./build.sh --game --debug
```

Once this is done, you can start the game by running the command
```
./game
```
You may also start with no saved data by running
```
./game --noSave
```

## Testing
You can compile and run the tests by running the following commands
```
./build.sh --tests
```

```
./test
```
you can also combine the arguments already mentioned, or use --all to compile both executables. For example, the following line will build both game and tests in debug mode :
```
./build.sh --all --debug
```
