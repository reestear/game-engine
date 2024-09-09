cmake_minimum_required(VERSION 3.20)
project(GameEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ENABLED_PCH ON)
set(ENABLED_BUFFERED_OUTPUT ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

# Not Working function :/
# function(engine_target_precompile_headers ARGV)
#     message(STATUS "ARGV: ${ARGV}")
#     if(ENABLED_PCH)
#         message(STATUS "Precompiling headers for target: ${ARGV}")
#         target_precompile_headers(${ARGV})
#     endif()
# endfunction()

# Set source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Set source subdirectories
file(GLOB_RECURSE ALL_ENTRIES LIST_DIRECTORIES true ${SRC_DIR}/*)
set(SRC_SUBDIRS "")
foreach(item ${ALL_ENTRIES})
    # message(STATUS "Currenly looking at item: ${item}")
    if(IS_DIRECTORY ${item})
        list(APPEND SRC_SUBDIRS ${item})
    endif()
endforeach()

# Set include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Printing Directories
# message(STATUS "Source directory: ${SRC_DIR}")

# foreach(dir ${SRC_SUBDIRS})
#     message(STATUS "Found directory: ${dir}")
# endforeach()

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
# find_package(tinyxml2 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TINYXML2 REQUIRED tinyxml2)


set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)
set(SDL2_TTF_LIBRARIES SDL2_ttf::SDL2_ttf)

include_directories(${INCLUDE_DIR})
include_directories("${INCLUDE_DIR}/constants")
include_directories(${SRC_SUBDIRS})
include_directories(${TINYXML2_INCLUDE_DIRS})

link_directories(${TINYXML2_LIBRARY_DIRS})

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

# Output directory for binaries
set(OUT_DIR ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

# Specify the executable and link libraries
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${TINYXML2_LIBRARIES})

message(STATUS "TINYXML2_LIBRARY_DIRS : ${TINYXML2_INCLUDE_DIRS} ${TINYXML2_LIBRARY_DIRS} ${TINYXML2_LIBRARIES}")

# Set PCH
if(ENABLED_PCH)
    message(STATUS "Precompiling headers for target: ${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/pch.h")
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/pch.h)
endif()

message(STATUS "Output directory: ${OUT_DIR}")

# Clean output directory
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${OUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_DIR}
)

# Add a 'run' target for convenience
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${OUT_DIR}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Some Playings

# message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
# message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
# message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
# message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
# message(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
# message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
# message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")

# set(MY_VAR "default_value")
# message("MY_VAR in CMakeLists.txt: ${MY_VAR}")
