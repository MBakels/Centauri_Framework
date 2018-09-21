# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Centauri_Framework)

# delete CMakeCache.txt from the build directory when you edit these options
############################################################################
OPTION(MAKE_DEMO "Make Framework demo (tests) application" ON)
OPTION(MAKE_SPACE_GAME_DEMO "Make Framework demo game" ON)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (external)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")
endif(UNIX)

if(WIN32)
	# Create a group for Visual Studio
	SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
	# suppress pedantic warnings
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

include_directories(
	external/glfw-3.2.1/include
	external/glm-0.9.8.5
	external/glad/include
	external/freetype-2.9.1/include
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
	centauri/input.cpp
	centauri/input.h
	centauri/singleton.h
	centauri/texture.h
	centauri/texture.cpp
	centauri/mesh.h
	centauri/mesh.cpp
	centauri/basicshapes.h
	centauri/basicshapes.cpp
	centauri/color.h
)

file(
	COPY centauri/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

# Demo
if(MAKE_DEMO)
	add_executable(demo
		projects/demo/main.cpp
		projects/demo/masterscene.cpp
		projects/demo/masterscene.h
		projects/demo/scene01.cpp
		projects/demo/scene01.h
		projects/demo/scene02.cpp
		projects/demo/scene02.h
	)
	
	target_link_libraries(demo
		${ALL_GRAPHICS_LIBS}
		freetype
	)
	
	file(
		COPY projects/demo/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)

endif()

# Space demo game
if(MAKE_SPACE_GAME_DEMO)
	add_executable(space_game
		projects/demo_space_game/main.cpp
		projects/demo_space_game/gamescene.cpp
		projects/demo_space_game/gamescene.h
		projects/demo_space_game/laser.cpp
		projects/demo_space_game/laser.h
		projects/demo_space_game/playership.cpp
		projects/demo_space_game/playership.h
		projects/demo_space_game/enemyship.cpp
		projects/demo_space_game/enemyship.h
	)
	
	target_link_libraries(space_game
		${ALL_GRAPHICS_LIBS}
		freetype
	)
	
	file(
		COPY projects/demo_space_game/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)

endif()










