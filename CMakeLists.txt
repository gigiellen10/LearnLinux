cmake_minimum_required(VERSION 3.30)
project(LearnLinux)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

add_executable(LearnLinux src/main.cpp src/game.cpp src/Linux.cpp)

# Below is code to link .csv files in build dir to those in program dir

# Directory paths
set(MAIN_DIR /Users/genevievekochel/Downloads/WSU_Classes/CPTS_223/PA/PA1)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# List of CSV files to link
set(CSV_FILES src/profiles.csv src/commands.csv)

# Function to create symbolic links
function(create_symlinks)
    foreach(file ${CSV_FILES})
        set(src "${MAIN_DIR}/${file}")
        set(dest "${BUILD_DIR}/${file}")
        if (EXISTS ${dest})
            file(REMOVE ${dest})
        endif()
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest})
    endforeach()
endfunction()

# Call the function to create the links
create_symlinks()

# Ensure symlinks are created before building the executable
add_custom_target(symlinks ALL DEPENDS ${CSV_FILES})
add_dependencies(LearnLinux symlinks)