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

set(SRC_DIR src)
set(RATYPES_DIR src/ra_types)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(RATYPES_SRC
    ${RATYPES_DIR}/rgb888.cpp
    )

set(EXAMPLES_DIRS
    ${SRC_DIR}/example_runner
    ${SRC_DIR}/examples
    ${SRC_DIR}/examples/cartesian2d
    )

set(EXAMPLES_SRC
    src/example_runner/ExampleRunner.cpp
    src/examples/ExamplePackBase.cpp
    src/examples/cartesian2d/01_Elementary.cpp
    )

set(CANVAS2DVIEWERS_DIR src/canvas2dViewers)

set(CANVAS2DVIEWERS_SRC
    ${CANVAS2DVIEWERS_DIR}/PpxCanvas2dViewer.cpp
    ${CANVAS2DVIEWERS_DIR}/TerminalCanvas2dViewer.cpp
    )

set(CORE_DIR src/core)
set(RENDER2D_DIR src/core/rendering2d)
set(CORE_DIRS
    ${CORE_DIR}/canvas2d/
    ${CORE_DIR}/figures2d/
    ${CORE_DIR}/figures2d/shapes/
    ${CORE_DIR}/figures2d/circuits/
    ${RENDER2D_DIR}
    ${RENDER2D_DIR}/circuits/
    ${RENDER2D_DIR}/clipping/
    ${RENDER2D_DIR}/filling/
    ${RENDER2D_DIR}/line/

    )
set(CORE_SRC
    ${CORE_DIR}/canvas2d/RectangularPixelBuffer.cpp
    ${CORE_DIR}/canvas2d/Canvas2d.cpp
    src/core/canvas2d/Rectangular1dDotBuffer.cpp
    src/core/canvas2d/DrawFigure2dVisitor.cpp
    src/core/figures2d/ShapeBase.cpp
    src/core/figures2d/CircuitBase.cpp
    src/core/figures2d/circuits/Dot.cpp
    src/core/figures2d/circuits/LineSegment.cpp
    src/core/figures2d/circuits/Circle.cpp
    src/core/rendering2d/line/algorithms_lines_naive.cpp
    src/core/rendering2d/line/algorithms_line_classic.cpp
    src/core/rendering2d/circuits/algorithms_circle.cpp
    src/core/canvas2d/AlgorithmProxy.cpp
    )

set(RASERVICES_DIR ${SRC_DIR}/ra_services)
set(RASERVICES_DIRS
    ${RASERVICES_DIR}/random_figure/
    ${RASERVICES_DIR}/geo_trans_homogen_coord/
    ${RASERVICES_DIR}/color_rgb/
    ${RASERVICES_DIR}/math2d/
    )

set(RASERVCIES_SRC
    src/ra_services/color_rgb/ColorMap.cpp
    )


set(SOURCES
    ${CORE_SRC}
    ${CANVAS2DVIEWERS_SRC}
    ${EXAMPLES_SRC}
    ${RATYPES_SRC}
    ${RASERVCIES_SRC}
    ${SRC_DIR}/main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIR}
    ${RATYPES_DIR}
    ${EXAMPLES_DIRS}
    ${CANVAS2DVIEWERS_DIR}
    ${CORE_DIRS}
    ${RASERVICES_DIRS}
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

message(">> CMakeLists for Rendering Algorithms: finished!")
