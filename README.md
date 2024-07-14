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
Install the required dependencies, then run the command
```
./build.sh
```

You may also build in debug mode by running 
```
./build.sh --debug
```


Then, to start the game, run 
```
./game
```

You may also start with no saved data by running
```
./game --noSave
```