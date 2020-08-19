cmake_minimum_required(VERSION 3.9)

message(">> CMakeLists for Rendering Algorithms: started...")

project(renderalgo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

message("It's need to find the dependencies...")

SET(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)

if(OPENGL_FOUND)
    message ("opengl found")
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    message (FATAL_ERROR "Cannot find OPENGL! Try to install mesa-libGL-devel mesa-libGLU-devel")
endif()

if(GLUT_FOUND)
    message ("glut found")
    include_directories(${GLUT_INCLUDE_DIR})
else()
    message (FATAL_ERROR "Cannot find glut! Try to install glut-devel package.")
endif()

set(SRC_DIR "src")

set(SOURCES
    ${SRC_DIR}/main.cpp
    )

add_executable (${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    )

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    OpenGL::GL
    ${GLUT_LIBRARIES}
    -lGLU
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin
        ARCHIVE DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)


if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /std:c++17")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -Werror")
endif()

message(">> CMakeLists for drawing_principles: finished!")
