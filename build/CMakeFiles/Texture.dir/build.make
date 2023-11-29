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
include CMakeFiles/Texture.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Texture.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Texture.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Texture.dir/flags.make

CMakeFiles/Texture.dir/src/Texture.cpp.o: CMakeFiles/Texture.dir/flags.make
CMakeFiles/Texture.dir/src/Texture.cpp.o: ../src/Texture.cpp
CMakeFiles/Texture.dir/src/Texture.cpp.o: CMakeFiles/Texture.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Texture.dir/src/Texture.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Texture.dir/src/Texture.cpp.o -MF CMakeFiles/Texture.dir/src/Texture.cpp.o.d -o CMakeFiles/Texture.dir/src/Texture.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/Texture.cpp

CMakeFiles/Texture.dir/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Texture.dir/src/Texture.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/Texture.cpp > CMakeFiles/Texture.dir/src/Texture.cpp.i

CMakeFiles/Texture.dir/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Texture.dir/src/Texture.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/Texture.cpp -o CMakeFiles/Texture.dir/src/Texture.cpp.s

# Object files for target Texture
Texture_OBJECTS = \
"CMakeFiles/Texture.dir/src/Texture.cpp.o"

# External object files for target Texture
Texture_EXTERNAL_OBJECTS =

libTexture.a: CMakeFiles/Texture.dir/src/Texture.cpp.o
libTexture.a: CMakeFiles/Texture.dir/build.make
libTexture.a: CMakeFiles/Texture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTexture.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Texture.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Texture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Texture.dir/build: libTexture.a
.PHONY : CMakeFiles/Texture.dir/build

CMakeFiles/Texture.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Texture.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Texture.dir/clean

CMakeFiles/Texture.dir/depend:
	cd /home/larziz/Dev/CPP/MarchingCubes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles/Texture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Texture.dir/depend
