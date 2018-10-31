cmake_minimum_required (VERSION 3.8)

set (MY_NAME "lissajous-curve-table")
project (${MY_NAME})

set (MY_FILES "main.cpp")

if (WIN32)
  link_directories (${MY_NAME} "lib")
  include_directories (${MY_NAME} "include")
endif (WIN32)

add_executable (${MY_NAME} ${MY_FILES})

if (UNIX)
    target_link_libraries (${MY_NAME} "GL" "GLU" "glut")
endif (UNIX)

if (WIN32)
    target_link_libraries (${MY_NAME} "freeglut")
    add_custom_command(TARGET ${MY_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/dll/freeglut.dll" ${CMAKE_BINARY_DIR})
endif (WIN32)