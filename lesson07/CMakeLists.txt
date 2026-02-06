cmake_minimum_required(VERSION 3.21)

project (occ-lesson07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp")
add_executable(occ-lesson07 ${SOURCES})

target_link_libraries(occ-lesson07
    PRIVATE
        glfw
        OpenGL::GL
        GLEW::GLEW
        glm::glm
)

target_compile_definitions(occ-lesson07 PRIVATE GLM_ENABLE_EXPERIMENTAL)

install(TARGETS occ-lesson07 DESTINATION bin)
