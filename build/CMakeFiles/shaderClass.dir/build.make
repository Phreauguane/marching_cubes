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
CMAKE_SOURCE_DIR = /home/larziz/Dev/CPP/MarchingCubes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/larziz/Dev/CPP/MarchingCubes/build

# Include any dependencies generated for this target.
include CMakeFiles/shaderClass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shaderClass.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shaderClass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shaderClass.dir/flags.make

CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o: CMakeFiles/shaderClass.dir/flags.make
CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o: ../src/shaderClass.cpp
CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o: CMakeFiles/shaderClass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o -MF CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o.d -o CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/shaderClass.cpp

CMakeFiles/shaderClass.dir/src/shaderClass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shaderClass.dir/src/shaderClass.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/shaderClass.cpp > CMakeFiles/shaderClass.dir/src/shaderClass.cpp.i

CMakeFiles/shaderClass.dir/src/shaderClass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shaderClass.dir/src/shaderClass.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/shaderClass.cpp -o CMakeFiles/shaderClass.dir/src/shaderClass.cpp.s

# Object files for target shaderClass
shaderClass_OBJECTS = \
"CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o"

# External object files for target shaderClass
shaderClass_EXTERNAL_OBJECTS =

libshaderClass.a: CMakeFiles/shaderClass.dir/src/shaderClass.cpp.o
libshaderClass.a: CMakeFiles/shaderClass.dir/build.make
libshaderClass.a: CMakeFiles/shaderClass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libshaderClass.a"
	$(CMAKE_COMMAND) -P CMakeFiles/shaderClass.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shaderClass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shaderClass.dir/build: libshaderClass.a
.PHONY : CMakeFiles/shaderClass.dir/build

CMakeFiles/shaderClass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shaderClass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shaderClass.dir/clean

CMakeFiles/shaderClass.dir/depend:
	cd /home/larziz/Dev/CPP/MarchingCubes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles/shaderClass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shaderClass.dir/depend

