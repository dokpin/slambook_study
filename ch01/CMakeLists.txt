cmake_minimum_required( VERSION 2.8 )
project( useHello )

add_executable( useHello useHello.cpp )
add_library( hello libHelloSLAM.cpp )
target_link_libraries( useHello hello)

