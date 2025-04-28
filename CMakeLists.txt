cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME leet)
set(TARGET_NAME ${PROJECT_NAME})

project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(LEET_EXECUTABLE_NAME "run")

add_subdirectory(1071_greatest_common_divisor_of_strings)
add_subdirectory(1679_max_number_of_k-sum_pairs)
