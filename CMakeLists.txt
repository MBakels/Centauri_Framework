# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Centauri_Framework)
find_package(OpenGL REQUIRED)

OPTION(MAKE_DEMO "Make Framework demo (tests) application" ON)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

	# For leak-checking and profiling, add '-pg' to CXX flags
	# set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11 -O2")
	# valgrind --leak-check=full ./demo
	# ./demo # creates cmon.out
	# gprof demo gmon.out > analysis.txt
endif(UNIX)

if(WIN32)
	# Create a group for Visual Studio
	SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
	# suppress pedantic warnings
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

# Compile external dependencies
add_subdirectory (external)

include_directories(
	external/glfw-3.2.1/include
	external/glm-0.9.8.5
	external/glad/include
	centauri
	.
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	centauri
	glfw
	GLAD
)

# Centauri_Framework lib
add_library(centauri
	centauri/camera.cpp
	centauri/camera.h
	centauri/config.h
	centauri/renderer.cpp
	centauri/renderer.h
	centauri/resourcemanager.cpp
	centauri/resourcemanager.h
	centauri/shader.cpp
	centauri/shader.h
	centauri/sprite.cpp
	centauri/sprite.h
	centauri/core.cpp
	centauri/core.h
	centauri/gameobject.cpp
	centauri/gameobject.h
	centauri/scene.cpp
	centauri/scene.h
	centauri/pointx.h
	centauri/vectorx.h
)

file(
	COPY centauri/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

# Demo
if(MAKE_DEMO)
	add_executable(demo
		projects/demo/main.cpp
		projects/demo/scene00.cpp
		projects/demo/scene00.h
	)
	
	target_link_libraries(demo
		${ALL_GRAPHICS_LIBS}
	)
	
	file(
		COPY projects/demo/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)

endif()












