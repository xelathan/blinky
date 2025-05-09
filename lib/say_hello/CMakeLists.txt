# say_hello lib
if (CONFIG_SAY_HELLO)

    zephyr_include_directories(include)

    zephyr_library_sources(src/say_hello.c)

endif()

# target_sources(app PRIVATE src/say_hello.c)

# target_include_directories(
#     app
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# # more libs...