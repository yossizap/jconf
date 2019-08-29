cmake_minimum_required(VERSION 3.10)
project(JConf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(JCONF_PUBLIC_HEADERS include/jconf/jconf.hpp)

add_library(JConf
    jconf.cpp
    ${JCONF_PUBLIC_HEADERS})
add_library(JConf::JConf ALIAS JConf)

target_include_directories(
    JConf PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(JConf
    PROPERTIES
    PUBLIC_HEADER ${JCONF_PUBLIC_HEADERS})

target_link_libraries(
    JConf
    PUBLIC json-schema-validator nlohmann_json)
