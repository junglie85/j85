add_executable(j85_test_test j85_test_test.c)

target_include_directories(j85 PUBLIC ../include)
target_link_libraries(j85_test_test PRIVATE j85)
