# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller

# Include any dependencies generated for this target.
include CMakeFiles/cpp_stepper_controller.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cpp_stepper_controller.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_stepper_controller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_stepper_controller.dir/flags.make

CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o: CMakeFiles/cpp_stepper_controller.dir/flags.make
CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o: /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller/src/cpp_stepper_controller.cpp
CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o: CMakeFiles/cpp_stepper_controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o -MF CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o.d -o CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o -c /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller/src/cpp_stepper_controller.cpp

CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller/src/cpp_stepper_controller.cpp > CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.i

CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller/src/cpp_stepper_controller.cpp -o CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.s

# Object files for target cpp_stepper_controller
cpp_stepper_controller_OBJECTS = \
"CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o"

# External object files for target cpp_stepper_controller
cpp_stepper_controller_EXTERNAL_OBJECTS =

cpp_stepper_controller: CMakeFiles/cpp_stepper_controller.dir/src/cpp_stepper_controller.cpp.o
cpp_stepper_controller: CMakeFiles/cpp_stepper_controller.dir/build.make
cpp_stepper_controller: CMakeFiles/cpp_stepper_controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpp_stepper_controller"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp_stepper_controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_stepper_controller.dir/build: cpp_stepper_controller
.PHONY : CMakeFiles/cpp_stepper_controller.dir/build

CMakeFiles/cpp_stepper_controller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp_stepper_controller.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp_stepper_controller.dir/clean

CMakeFiles/cpp_stepper_controller.dir/depend:
	cd /home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller /home/seds/Desktop/TERRANCE/Terrance/src/cpp_stepper_controller /home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller /home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller /home/seds/Desktop/TERRANCE/Terrance/src/build/cpp_stepper_controller/CMakeFiles/cpp_stepper_controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp_stepper_controller.dir/depend

