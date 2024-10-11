cmake_minimum_required(VERSION 3.15)
project(walk-gen VERSION 1.0 LANGUAGES CXX)

add_executable(walk-gen src/walkrun.cpp src/Walk.cpp src/DLA.cpp)
target_compile_features(walk-gen PUBLIC cxx_std_11)

# Testing
option(BUILD_TESTING "Build the testing tree." OFF)

include(CTest)
enable_testing()

if(BUILD_TESTING MATCHES ON)
    set(FETCHCONTENT_QUIET FALSE)

    # Fetch Catch2
    include(FetchContent)
    FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0 # Or any stable release
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(catch)

    # Create a test executable
    add_executable(tests src/tests/test_vector.cpp)
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

    # Add the test
    add_test(NAME MyTests COMMAND tests)
endif()
