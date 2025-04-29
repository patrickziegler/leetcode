find_package(GTest REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "735_asteroid_collision.cpp"
    "1071_greatest_common_divisor_of_strings.cpp"
    "1657_determine_if_two_strings_are_close.cpp"
    "1679_max_number_of_k-sum_pairs.cpp"
    "2352_equal_row_and_column_pairs.cpp")

target_link_libraries(${TARGET_NAME}
    GTest::GTest GTest::Main)

gtest_discover_tests(${TARGET_NAME})

enable_testing()
