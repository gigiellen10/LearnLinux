# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/build

# Utility rule file for symlinks.

# Include any custom commands dependencies for this target.
include CMakeFiles/symlinks.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/symlinks.dir/progress.make

CMakeFiles/symlinks: /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/src/profiles.csv
CMakeFiles/symlinks: /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/src/commands.csv

symlinks: CMakeFiles/symlinks
symlinks: CMakeFiles/symlinks.dir/build.make
.PHONY : symlinks

# Rule to build all files generated by this target.
CMakeFiles/symlinks.dir/build: symlinks
.PHONY : CMakeFiles/symlinks.dir/build

CMakeFiles/symlinks.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/symlinks.dir/cmake_clean.cmake
.PHONY : CMakeFiles/symlinks.dir/clean

CMakeFiles/symlinks.dir/depend:
	cd /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/build /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/build /Users/genevievekochel/Downloads/PersonalProjects/LearnLinux/build/CMakeFiles/symlinks.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/symlinks.dir/depend

