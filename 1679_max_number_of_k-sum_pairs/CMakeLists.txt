set(TARGET_NAME 1679)

add_executable(${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
    OUTPUT_NAME ${LEET_EXECUTABLE_NAME})

target_sources(${TARGET_NAME} PRIVATE
    "main.cpp")
