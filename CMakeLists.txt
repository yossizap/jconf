cmake_minimum_required(VERSION 3.14)
project(JConf VERSION 0.1.0 LANGUAGES CXX)

option(JCONF_USE_EXTERNAL_JSON "Use an external JSON library" OFF)
add_subdirectory(third_party)

add_subdirectory(src)
add_subdirectory(test)
