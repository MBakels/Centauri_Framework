# CMake entry point
cmake_minimum_required (VERSION 3.10)
project (Centauri_Framework)

# delete CMakeCache.txt from the build directory when you edit these options
############################################################################
OPTION(MAKE_DEMO "Make Framework demo (tests) application" ON)
OPTION(MAKE_SPACE_GAME_DEMO "Make Framework demo game" ON)
OPTION(MAKE_PINGUIN_WARFARE "Make the game" ON)

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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
	external/stb/include
	centauri
	.
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	centauri
	glfw
	GLAD
	freetype
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
	centauri/text.h
	centauri/text.cpp
	centauri/font.h
	centauri/font.cpp
	centauri/math/time.h
	centauri/math/time.cpp
	centauri/textfile.cpp
	centauri/textfile.h
	centauri/ui/button.cpp
	centauri/ui/button.h
	centauri/scenemanager.cpp
	centauri/scenemanager.h
)

file(
	COPY centauri/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

file(
	COPY centauri/fonts
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
		projects/demo/scene03.cpp
		projects/demo/scene03.h
	)
	
	target_link_libraries(demo
		${ALL_GRAPHICS_LIBS}
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
	)
	
	file(
		COPY projects/demo_space_game/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)

endif()

# Pinguin warfare
if(MAKE_PINGUIN_WARFARE)
	add_executable(pinguin_warfare
		projects/pinguin_warfare/main.cpp
		projects/pinguin_warfare/map.cpp
		projects/pinguin_warfare/map.h
		projects/pinguin_warfare/tile.cpp
		projects/pinguin_warfare/tile.h
		projects/pinguin_warfare/pinguin.cpp
		projects/pinguin_warfare/pinguin.h
		projects/pinguin_warfare/mainmenuscene.cpp
		projects/pinguin_warfare/mainmenuscene.h
		projects/pinguin_warfare/pausemenu.cpp
		projects/pinguin_warfare/pausemenu.h
		projects/pinguin_warfare/snowball.cpp
		projects/pinguin_warfare/snowball.h
		projects/pinguin_warfare/mapselectionmenuscene.cpp
		projects/pinguin_warfare/mapselectionmenuscene.h
		projects/pinguin_warfare/winmenuscene.cpp
		projects/pinguin_warfare/winmenuscene.h
		projects/pinguin_warfare/deathmenuscene.cpp
		projects/pinguin_warfare/deathmenuscene.h
		projects/pinguin_warfare/mapmaker.cpp
		projects/pinguin_warfare/mapmaker.h
	)
	
	target_link_libraries(pinguin_warfare
		${ALL_GRAPHICS_LIBS}
	)
	
	file(
		COPY projects/pinguin_warfare/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
	
	file(
		COPY projects/pinguin_warfare/maps
		DESTINATION ${CMAKE_BINARY_DIR}
	)

endif()










