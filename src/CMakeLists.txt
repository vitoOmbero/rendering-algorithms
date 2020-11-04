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

set(SRC_DIR .)
set(RATYPES_DIR ra_types)
set(INCLUDE_DIR include)

set(RATYPES_SRC
    ##currently no any sources!
    )

set(RATYPES_DIRS
    ${RATYPES_DIR}/
    ${RATYPES_DIR}/2d/
    )

set(EXAMPLES_DIRS
    ${SRC_DIR}/example_runner
    ${SRC_DIR}/examples
    ${SRC_DIR}/examples/cartesian2d
    )

set(EXAMPLES_SRC
        example_runner/example_runner.cpp
        examples/example_pack_base.cpp
        examples/cartesian2d/01_elementary.cpp
        examples/cartesian2d/02_shapes.cpp
        examples/cartesian2d/03_clipping.cpp
        examples/cartesian2d/04_transitions.cpp
        examples/cartesian2d/05_shaders.cpp
    )

set(CANVAS2DVIEWERS_DIR canvas2dViewers)

set(CANVAS2DVIEWERS_SRC
    ${CANVAS2DVIEWERS_DIR}/ppx_canvas2d_viewer.cpp
    ${CANVAS2DVIEWERS_DIR}/terminal_canvas2d_viewer.cpp
    )

set(CORE_DIR core)
set(RENDER2D_DIR core/rendering2d)
set(CORE_DIRS
    ${CORE_DIR}/pipeline/
    ${CORE_DIR}/figures2d/
    ${CORE_DIR}/figures2d/visitors/
    ${CORE_DIR}/figures2d/shapes/
    ${CORE_DIR}/figures2d/circuits/
    ${RENDER2D_DIR}/
    ${RENDER2D_DIR}/circuits/
    ${RENDER2D_DIR}/clipping/
    ${RENDER2D_DIR}/filling/
    ${RENDER2D_DIR}/line/
    )
set(CORE_SRC
    ${CORE_DIR}/pipeline/pixel_buffer2d.cpp
        core/pipeline/dot_linear_buffer2d.cpp
        core/figures2d/visitors/draw_circuit2d_visitor.cpp
        core/figures2d/visitors/draw_shape2d_visitor.cpp
        core/figures2d/shape_base.cpp
        core/figures2d/circuit_base.cpp
        core/figures2d/circuits/dot.cpp
        core/figures2d/circuits/line_segment.cpp
        core/figures2d/circuits/circle.cpp
        core/figures2d/circuits/triangle.cpp
        core/figures2d/circuits/quadrangle.cpp
        core/rendering2d/line/algorithms_lines_naive.cpp
        core/rendering2d/line/algorithms_line_classic.cpp
        core/rendering2d/circuits/algorithms_circle.cpp
        core/rendering2d/filling/algorithms_filling_naive.cpp
        core/rendering2d/filling/algorithm_filling_3v_line_sweeping.cpp
        core/rendering2d/clipping/algorithm_clipping_cohen_sutherland_int.cpp
        core/rendering2d/clipping/algorithm_clipping_cyrus_beck_int.cpp
        core/pipeline/algorithm_proxy.cpp
        core/pipeline/clipping_rectangular_window.cpp
        core/pipeline/renderer.cpp
        core/pipeline/rasterizer_simple.cpp
        core/pipeline/space_coordinate_translator_simple.cpp
        core/pipeline/pipeline.cpp
    )

set(RASERVICES_DIR ${SRC_DIR}/ra_services)
set(RASERVICES_DIRS
    ${RASERVICES_DIR}/
    ${RASERVICES_DIR}/random_figure/
    ${RASERVICES_DIR}/geo_trans_homogen_coord/
    ${RASERVICES_DIR}/color_rgb/
    ${RASERVICES_DIR}/math2d/
    ${RASERVICES_DIR}/get_string/
    )

set(RASERVCIES_SRC
        ra_services/color_rgb/color_map.cpp
        ra_services/geo_trans_homogen_coord/matrix_calculator_simple.cpp
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
    ${RATYPES_DIRS}
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

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /std:c++17")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -Werror")
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../install/
        LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../install/
        ARCHIVE DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../install/)

message(">> CMakeLists for Rendering Algorithms: finished!")
