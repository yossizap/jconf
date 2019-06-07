enable_testing()
add_executable(JConfTest test.cpp)
target_link_libraries(JConfTest PRIVATE JConf::JConf)

add_custom_command(TARGET JConfTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/config $<TARGET_FILE_DIR:JConfTest>)
