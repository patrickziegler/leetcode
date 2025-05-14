find_package(GTest REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "216_combination_sum_3.cpp"
    "394_decode_string.cpp"
    "399_evaluate_division.cpp"
    "450_delete_node_in_a_bst.cpp"
    "649_dota2_senate.cpp"
    "735_asteroid_collision.cpp"
    "875_koko_eating_bananas.cpp"
    "1071_greatest_common_divisor_of_strings.cpp"
    "1143_longest_common_subsequence.cpp"
    "1657_determine_if_two_strings_are_close.cpp"
    "1679_max_number_of_k-sum_pairs.cpp"
    "2300_successful_pairs_of_spells_and_potions.cpp"
    "2352_equal_row_and_column_pairs.cpp"
    "2462_total_cost_to_hire_k_workers.cpp"
    "2542_maximum_subsequence_score.cpp")

target_link_libraries(${TARGET_NAME}
    GTest::GTest GTest::Main)

gtest_discover_tests(${TARGET_NAME})

enable_testing()
