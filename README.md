# Tanks Game in 2D

## Description
Welcome to the thrilling world of Tank Battle, a 2D game programmed in C++ using the SFML library for graphics, Nlohmann json library for dynamic map configuration, and gtest library for testing. The project is structured with CMake version 3.12 and adheres to C++17 standards, ensuring a modern and efficient codebase.

## Project Minimum Requirements
 - SFML Library
 - Nlohmann json Library
 - gtest Library
 - CMake Version 3.12
 - C++17

## Installing Requirements
 The most simple way to install the required libraries is using Vcpkg

### Install vcpkg
Installing vcpkg is a two-step process: first, clone the repo, then run the bootstrapping script to produce the vcpkg binary. The repo can be cloned anywhere, and will include the vcpkg binary after bootstrapping as well as any libraries that are installed from the command line. It is recommended to clone vcpkg as a submodule to an existing project if possible for greater flexibility.

#### Step 1: Clone the vcpkg repo

```
git clone https://github.com/Microsoft/vcpkg.git

```
Make sure you are in the directory you want the tool installed to before doing this.

#### Step 2: Run the bootstrap script to build vcpkg

```
./vcpkg/bootstrap-vcpkg.sh

```

Install libraries for your project, in example:

```
vcpkg install gtest

```


### Using vcpkg with CMake
In order to use vcpkg with CMake outside of an IDE, you can use the toolchain file:
cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake

### Then build with:

cmake --build [build directory]

With CMake, you will need to find_package() to reference the libraries in your CMakeLists.txt files.


## Roadmap Progress:

1. Basic Project Structure:

  Set up a well-organized project structure for scalability and maintainability. 

2. Tank Movement:

  Implement smooth and responsive tank movement controls.

3. Simple UI using SFML:

  Create an intuitive user interface with SFML for an engaging gaming experience.

4. Tank Shooting:

  Integrate tank shooting mechanics, allowing players to engage in epic battles.

5. Collision Detection:

  Implement precise collision detection to enhance gameplay realism.

6. Adaptive Time Step Game Loop:

  Synchronize the game loop using the Adaptive Time Step method for consistent performance across different systems.

7. Artwork Design:

  Craft visually appealing graphics and artwork to enhance the overall aesthetics of the game.

8. Dynamic Map System with JSON:

  Create a dynamic map system using a JSON file for easy customization and level design.

9. Animations:

Integrate animations to bring the game to life, adding dynamic elements to gameplay.

10. Test and Bug Fixes:

Conduct thorough testing and address any bugs or issues to ensure a stable gaming experience.
Upcoming Tasks:

## Upcoming Tasks:

1. Bot Tanks for Single Player:

Develop and implement AI-controlled bot tanks to provide a challenging single-player experience. Enhance their behavior to simulate intelligent and engaging opponents.

2. Basic Networking with Boost.Asio:

Integrate Boost.Asio for basic networking capabilities, setting the foundation for multiplayer functionality.

3. Basic Multiplayer Functionality:

Implement basic multiplayer features to allow players to engage in exciting battles against each other.

4. Fine-tune Multiplayer Synchronization:

Optimize and refine multiplayer synchronization for a seamless gaming experience.

5. Game Over Conditions:

Implement conditions that determine when the game ends, providing closure to each match.

6. Scoring System:

Introduce a scoring system to track player performance and determine winners.

7. Sound Effects and UI Polish:

Enhance the gaming experience with immersive sound effects and polish the user interface for a professional look.

8. Thorough Testing and Bug Fixes:

Conduct extensive testing to identify and fix any remaining bugs or issues.