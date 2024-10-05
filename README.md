# LearnLinux

Core Functionalities: 1) Display game rules, 2) Play the game, 3) Load a previous game instance, 4) Add a new Linux command + definition, 5) Remove an existing Linux Command, 6) Exit the game and save progress to commands.csv and profiles.csv.

Cross-platform compilation enabled via CMake. Make sure CMake is installed and the current version matches the version minimum in CMakeLists.txt. To run the game, complete the following steps:
1. Clone git repo
2. Cd into the project on local file system
3. To create a build directory run command: mkdir build
4. Cd into the build folder
5. To build the project, run command: cmake ..
6. Run: cmake --build .
7. Run the generated executable via the command: ./LearnLinux
