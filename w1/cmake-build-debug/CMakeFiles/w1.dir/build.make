# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/snikolayen/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/snikolayen/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/snikolayen/cpp_red/w1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/snikolayen/cpp_red/w1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/w1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/w1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/w1.dir/flags.make

CMakeFiles/w1.dir/logger.cpp.o: CMakeFiles/w1.dir/flags.make
CMakeFiles/w1.dir/logger.cpp.o: ../logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/snikolayen/cpp_red/w1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/w1.dir/logger.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/w1.dir/logger.cpp.o -c /Users/snikolayen/cpp_red/w1/logger.cpp

CMakeFiles/w1.dir/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/w1.dir/logger.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/snikolayen/cpp_red/w1/logger.cpp > CMakeFiles/w1.dir/logger.cpp.i

CMakeFiles/w1.dir/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/w1.dir/logger.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/snikolayen/cpp_red/w1/logger.cpp -o CMakeFiles/w1.dir/logger.cpp.s

# Object files for target w1
w1_OBJECTS = \
"CMakeFiles/w1.dir/logger.cpp.o"

# External object files for target w1
w1_EXTERNAL_OBJECTS =

w1: CMakeFiles/w1.dir/logger.cpp.o
w1: CMakeFiles/w1.dir/build.make
w1: CMakeFiles/w1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/snikolayen/cpp_red/w1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable w1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/w1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/w1.dir/build: w1

.PHONY : CMakeFiles/w1.dir/build

CMakeFiles/w1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/w1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/w1.dir/clean

CMakeFiles/w1.dir/depend:
	cd /Users/snikolayen/cpp_red/w1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/snikolayen/cpp_red/w1 /Users/snikolayen/cpp_red/w1 /Users/snikolayen/cpp_red/w1/cmake-build-debug /Users/snikolayen/cpp_red/w1/cmake-build-debug /Users/snikolayen/cpp_red/w1/cmake-build-debug/CMakeFiles/w1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/w1.dir/depend
