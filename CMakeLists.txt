cmake_minimum_required(VERSION 3.10)

set(CPPS "src/main.cpp" "src/Router.cpp" "src/POV.cpp" "src/fairy_tail.cpp" "src/util.cpp")

project(VolgaIT)

add_executable(main ${CPPS})
