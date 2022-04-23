cmake_minimum_required(VERSION 2.6)

# set the project name and version
project (Estenografia)

set (CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

ADD_LIBRARY( Clases
	EstenografoLSB.h
	EstenografoLSB.cpp
)

include_directories(${OpenCV_INCLUDE_DIRS}) # not needed for opencv>=4.0
add_executable(Esteno Esteno.cpp)
target_link_libraries(Esteno ${OpenCV_LIBS})
target_link_libraries(Esteno stdc++fs)
target_link_libraries(Esteno Clases)
