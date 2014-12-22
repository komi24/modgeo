#CMakeLists.txt to build project using cmake
#run $cmake CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(ensimag_synthese)

include_directories(external/perlin/ lib3d/ libmesh/ libnavigation/ libperlin/ local/)

FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

INCLUDE(${QT_USE_FILE})


include_directories(${OPENGL_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

set(ensimag_surface_UI
   gui/mainwindow.ui
   gui/mesh_debug.ui
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
QT4_WRAP_UI(source_files_UI_H ${ensimag_surface_UI} )


file(
  GLOB_RECURSE 
  source_files
  external/* lib3d/*  libmesh/* libnavigation/* libperlin/* local/*
)

QT4_WRAP_CPP(source_files_moc local/window.hpp local/glwidget.hpp local/window_mesh_debug.hpp)


add_executable(
  ensimag_synthese
  ${source_files}
  ${source_files_UI_H}
  ${source_files_moc}
)

target_link_libraries(ensimag_synthese ${QT_LIBRARIES} ${QT_GL_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${OPENGL_LIBRARIES})
