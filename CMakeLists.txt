# CMakeList.txt : CMake project for Kurvendiskussion, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Kurvendiskussion")


add_executable (Kurvendiskussion "main.cpp"  "Nullstellen/Zeros.cpp" "Nullstellen/Zeros.hpp" "Derivation/Derivation.cpp" "Derivation/Derivation.hpp" "Graph/Graph.cpp" "Graph/Graph.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kurvendiskussion PROPERTY CXX_STANDARD 23)
endif()
