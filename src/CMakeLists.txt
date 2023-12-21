file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(TARGETS "")
foreach(src_file ${SRC_FILES})
    file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR} ${src_file})
    list(APPEND TARGETS ${relative_path})
    message("target added: ${relative_path}")
endforeach()

#message("TARGETS: ${TARGETS}")
add_executable(tanks ${TARGETS})
target_link_libraries(tanks PRIVATE sfml-graphics)
target_link_libraries(tanks PRIVATE nlohmann_json::nlohmann_json)


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tanks PRIVATE 
        -g
        -Wall
        -Wextra
        #-Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(tanks PRIVATE
        /EHsc
        /W4
        #/WX
    )
endif()