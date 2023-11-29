cmake_minimum_required(VERSION 3.0.0)
project(OpenGL_Template VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(OpenGL_Template 
	src/glad.c
	src/glad.h
	src/main.cpp
	src/app.hpp
	src/mainLoop.hpp
	src/controls.cpp
	src/controls.hpp
	src/marchingCubes.cpp
	src/marchingCubes.h
	src/noise.cpp
	src/noise.h
)
target_link_libraries(OpenGL_Template 
	glfw
	OpenGL::GL
)