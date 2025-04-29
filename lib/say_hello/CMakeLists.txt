# say_hello lib
target_sources(app PRIVATE src/say_hello.c)

target_include_directories(
    app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# more libs...