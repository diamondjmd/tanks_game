# Add the path to your custom libraries
find_package(GTest CONFIG REQUIRED)
enable_testing()
file(GLOB_RECURSE SRC_FILES_GAME CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../src/game/*.cpp")
file(GLOB_RECURSE SRC_FILES_ENGINE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/*.cpp")
file(GLOB TESTS_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

message( "Combination  TEST and SRC in TEST: ${TESTS_FILES} ${SRC_FILES} ${SRC_FILES_ENGINE}" )
add_executable(tests ${TESTS_FILES} ${SRC_FILES_GAME} ${SRC_FILES_ENGINE})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tests PRIVATE 
        -g
        -Wall
        -Wextra
       # -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(tests PRIVATE
        /EHsc
        /W4
      #  /WX
    )
endif()

target_compile_features(tests PUBLIC cxx_std_17)
target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main sfml-graphics)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src/game)  
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src/engine) 

