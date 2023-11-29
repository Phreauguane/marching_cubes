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
include CMakeFiles/OpenGL_Template.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGL_Template.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGL_Template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGL_Template.dir/flags.make

CMakeFiles/OpenGL_Template.dir/src/glad.c.o: CMakeFiles/OpenGL_Template.dir/flags.make
CMakeFiles/OpenGL_Template.dir/src/glad.c.o: ../src/glad.c
CMakeFiles/OpenGL_Template.dir/src/glad.c.o: CMakeFiles/OpenGL_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OpenGL_Template.dir/src/glad.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OpenGL_Template.dir/src/glad.c.o -MF CMakeFiles/OpenGL_Template.dir/src/glad.c.o.d -o CMakeFiles/OpenGL_Template.dir/src/glad.c.o -c /home/larziz/Dev/CPP/MarchingCubes/src/glad.c

CMakeFiles/OpenGL_Template.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OpenGL_Template.dir/src/glad.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/glad.c > CMakeFiles/OpenGL_Template.dir/src/glad.c.i

CMakeFiles/OpenGL_Template.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OpenGL_Template.dir/src/glad.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/glad.c -o CMakeFiles/OpenGL_Template.dir/src/glad.c.s

CMakeFiles/OpenGL_Template.dir/src/main.cpp.o: CMakeFiles/OpenGL_Template.dir/flags.make
CMakeFiles/OpenGL_Template.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/OpenGL_Template.dir/src/main.cpp.o: CMakeFiles/OpenGL_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OpenGL_Template.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL_Template.dir/src/main.cpp.o -MF CMakeFiles/OpenGL_Template.dir/src/main.cpp.o.d -o CMakeFiles/OpenGL_Template.dir/src/main.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/main.cpp

CMakeFiles/OpenGL_Template.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_Template.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/main.cpp > CMakeFiles/OpenGL_Template.dir/src/main.cpp.i

CMakeFiles/OpenGL_Template.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_Template.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/main.cpp -o CMakeFiles/OpenGL_Template.dir/src/main.cpp.s

CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o: CMakeFiles/OpenGL_Template.dir/flags.make
CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o: ../src/controls.cpp
CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o: CMakeFiles/OpenGL_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o -MF CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o.d -o CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/controls.cpp

CMakeFiles/OpenGL_Template.dir/src/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_Template.dir/src/controls.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/controls.cpp > CMakeFiles/OpenGL_Template.dir/src/controls.cpp.i

CMakeFiles/OpenGL_Template.dir/src/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_Template.dir/src/controls.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/controls.cpp -o CMakeFiles/OpenGL_Template.dir/src/controls.cpp.s

CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o: CMakeFiles/OpenGL_Template.dir/flags.make
CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o: ../src/marchingCubes.cpp
CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o: CMakeFiles/OpenGL_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o -MF CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o.d -o CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/marchingCubes.cpp

CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/marchingCubes.cpp > CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.i

CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/marchingCubes.cpp -o CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.s

CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o: CMakeFiles/OpenGL_Template.dir/flags.make
CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o: ../src/noise.cpp
CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o: CMakeFiles/OpenGL_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o -MF CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o.d -o CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o -c /home/larziz/Dev/CPP/MarchingCubes/src/noise.cpp

CMakeFiles/OpenGL_Template.dir/src/noise.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_Template.dir/src/noise.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larziz/Dev/CPP/MarchingCubes/src/noise.cpp > CMakeFiles/OpenGL_Template.dir/src/noise.cpp.i

CMakeFiles/OpenGL_Template.dir/src/noise.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_Template.dir/src/noise.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larziz/Dev/CPP/MarchingCubes/src/noise.cpp -o CMakeFiles/OpenGL_Template.dir/src/noise.cpp.s

# Object files for target OpenGL_Template
OpenGL_Template_OBJECTS = \
"CMakeFiles/OpenGL_Template.dir/src/glad.c.o" \
"CMakeFiles/OpenGL_Template.dir/src/main.cpp.o" \
"CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o" \
"CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o" \
"CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o"

# External object files for target OpenGL_Template
OpenGL_Template_EXTERNAL_OBJECTS =

OpenGL_Template: CMakeFiles/OpenGL_Template.dir/src/glad.c.o
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/src/main.cpp.o
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/src/controls.cpp.o
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/src/marchingCubes.cpp.o
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/src/noise.cpp.o
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/build.make
OpenGL_Template: /usr/lib/x86_64-linux-gnu/libGLX.so
OpenGL_Template: /usr/lib/x86_64-linux-gnu/libOpenGL.so
OpenGL_Template: CMakeFiles/OpenGL_Template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable OpenGL_Template"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGL_Template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGL_Template.dir/build: OpenGL_Template
.PHONY : CMakeFiles/OpenGL_Template.dir/build

CMakeFiles/OpenGL_Template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGL_Template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGL_Template.dir/clean

CMakeFiles/OpenGL_Template.dir/depend:
	cd /home/larziz/Dev/CPP/MarchingCubes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build /home/larziz/Dev/CPP/MarchingCubes/build/CMakeFiles/OpenGL_Template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGL_Template.dir/depend

