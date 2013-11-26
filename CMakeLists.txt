cmake_minimum_required( VERSION 2.6 )
project( Vedraw )
find_package( Qt5Widgets REQUIRED )

# Run moc when necessary:
set( CMAKE_AUTOMOC ON )
# As moc files are generated in the binary dir, tell CMake to always look for includes there:
set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( project_root ${CMAKE_SOURCE_DIR} )
set( src_dir ${project_root}/src )
set( vedraw_srcs
    ${src_dir}/main.cpp
    ${src_dir}/app/app_info.cpp
    ${src_dir}/colors/arithmetic_color_transform.cpp
    ${src_dir}/colors/color_components.cpp
    ${src_dir}/colors/simple_color_transforms.cpp
    ${src_dir}/drawing/drawing.cpp
    ${src_dir}/geometry/projective_transform.cpp
    ${src_dir}/gui/drawing_view.cpp
    ${src_dir}/gui/main_window.cpp
    ${src_dir}/gui/modifiers_applier.cpp
    ${src_dir}/modifiers/filters/color_map_filter.cpp
)

include_directories( ${src_dir} )

add_executable( vedraw  ${vedraw_srcs} )
target_link_libraries( vedraw ${Qt5Widgets_LIBRARIES} )
qt5_use_modules( vedraw Widgets )

add_definitions("-std=c++11")

set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-align -Wunused -Wformat=2 -Wcast-qual -Wold-style-cast -Woverloaded-virtual -Wshadow -Wnon-virtual-dtor -Werror" )
set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" )
