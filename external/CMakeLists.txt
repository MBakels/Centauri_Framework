if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
    add_definitions( "/MP" )
endif()

### GLFW ###

add_subdirectory (glfw-3.2.1)

include_directories(
    glfw-3.2.1/include/GLFW
    glad/include
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
    ${OPENGL_LIBRARY}
    -lGL -lGLU -lXrandr -lXext -lX11 -lrt
    ${CMAKE_DL_LIBS}
    ${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
    ${OPENGL_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLAD_SOURCE
    glad/src/glad.c
)

set(GLAD_HEADERS
)

add_library( GLAD STATIC
    ${GLAD_SOURCE}
    ${GLAD_INCLUDE}
)

target_link_libraries(GLAD
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
)




