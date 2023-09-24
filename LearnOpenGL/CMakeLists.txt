cmake_minimum_required(VERSION 3.2)

project(LearnOpenGL)

file(GLOB_RECURSE DIR_SRCS ./src/*.cpp ./src/*.c)
file(GLOB_RECURSE DIR_SRCS_HEADERS ./src/*.h)
file(GLOB_RECURSE DIR_SRCS_3RD ../3rd/Imgui/*)
# aux_source_directory(./src DIR_SRCS)
add_subdirectory(../3rd/glfw-3.3.8/glfw-3.3.8 glfw)
list(APPEND EXTRA_LIBS glfw)
list(APPEND EXTRA_INCLUDES ../3rd/glad/include)
list(APPEND EXTRA_INCLUDES ../3rd/glfw-3.3.8/glfw-3.3.8/include)
list(APPEND EXTRA_INCLUDES ../3rd/Imgui)

add_executable(LearnOpenGL ${DIR_SRCS} ${DIR_SRCS_HEADERS} ${DIR_SRCS_3RD})

target_link_libraries(LearnOpenGL PUBLIC ${EXTRA_LIBS})

target_include_directories(LearnOpenGL PUBLIC ${EXTRA_INCLUDES})