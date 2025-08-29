
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_version
  test_version.cpp
)

target_include_directories(test_version
    PRIVATE "${CMAKE_SOURCE_DIR}"
)

#how to target library from lib above
target_link_libraries(
  test_version
  GTest::gtest_main
  helloworld 
)


include(GoogleTest)
gtest_discover_tests(test_version)



if(MSVC)
    target_compile_options(test_version PRIVATE /W4)
else()
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

