enable_testing()
add_executable(JConfTest test.cpp)
target_link_libraries(JConfTest PRIVATE JConf::JConf)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3 -Wall -pedantic")

add_custom_command(TARGET JConfTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/config $<TARGET_FILE_DIR:JConfTest>)
