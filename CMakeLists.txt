cmake_minimum_required( VERSION 2.6 )
project( Vedraw )
find_package( Qt4 REQUIRED )

set( project_root ${CMAKE_SOURCE_DIR} )
set( src_dir ${project_root}/src )
set( vedraw_srcs ${src_dir}/main.cpp )

include_directories( ${QT_INCLUDES} ${src_dir} )
qt4_automoc( ${vedraw_srcs} )
add_executable( vedraw  ${vedraw_srcs} )
target_link_libraries( vedraw ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )

set( CMAKE_CXX_FLAGS "--std=c++0x -Wall -Wextra" )
set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" )
