cmake_minimum_required(VERSION 3.10)
project(JConf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
option(JCONF_USE_EXTERNAL_JSON "Use an external JSON library" OFF)
add_subdirectory(third_party)

add_subdirectory(src)
add_subdirectory(test)
