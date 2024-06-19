cmake_minimum_required(VERSION 3.20)
project(GameEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENABLED_PCH ON)

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
find_package(tinyxml2 REQUIRED)

set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)
set(SDL2_TTF_LIBRARIES SDL2_ttf::SDL2_ttf)

include_directories(${INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_DIRS})
include_directories(${SRC_SUBDIRS})

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

# Output directory for binaries
set(OUT_DIR ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

# Specify the executable and link libraries
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Set PCH
if(ENABLED_PCH)
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
