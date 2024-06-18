cmake_minimum_required(VERSION 3.10)
project(GameEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

#---------------------------------------------------S
# Printing Directories
# message(STATUS "Source directory: ${SRC_DIR}")

# foreach(dir ${SRC_SUBDIRS})
#     message(STATUS "Found directory: ${dir}")
# endforeach()
#---------------------------------------------------E

#---------------------------------------------------S
# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)
#---------------------------------------------------E

set(SDL2_IMAGE_INCLUDE_DIRS ${_sdl2image_incdir})
set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)

# set(SDL2_TTF_INCLUDE_DIRS ${_sdl2ttf_incdir})
# set(SDL2_TTF_LIBRARIES SDL2_ttf::SDL2_ttf)

include_directories(${INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
# include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SRC_SUBDIRS})

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

# Output directory for binaries
set(OUT_DIR ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

# Specify the executable and link libraries
add_executable(${PROJECT_NAME} ${SRC_FILES})
# target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

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
