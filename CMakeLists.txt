project(MatlabVis)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})




add_executable( main main.cpp PrepareForTubeFilter.cpp )
target_link_libraries (main ${VTK_LIBRARIES})
install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT comp_one)


add_executable( DainiausUzdavinys DainiausUzdavinys.cpp PrepareForTubeFilter.cpp Functions.cpp)
target_link_libraries (DainiausUzdavinys ${VTK_LIBRARIES})
install(TARGETS DainiausUzdavinys DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT comp_one)

