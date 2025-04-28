find_package(GTest REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "1071_greatest_common_divisor_of_strings.cpp"
    "1679_max_number_of_k-sum_pairs.cpp")

target_link_libraries(${TARGET_NAME}
    GTest::GTest GTest::Main)

gtest_discover_tests(${TARGET_NAME})

enable_testing()
