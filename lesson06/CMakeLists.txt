cmake_minimum_required(VERSION 3.21)

project (occ-lesson06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

file(GLOB SOURCES "*.cpp")
add_executable(occ-lesson06 ${SOURCES})

target_link_libraries(occ-lesson06
    PRIVATE
        glfw
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        PNG::PNG
        ZLIB::ZLIB
)

target_compile_definitions(occ-lesson06 PRIVATE GLM_ENABLE_EXPERIMENTAL)

install(TARGETS occ-lesson06 DESTINATION bin)
