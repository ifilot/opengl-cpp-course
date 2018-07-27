# set minimum cmake requirements
cmake_minimum_required(VERSION 2.8)
project (occ-lesson01)

# add custom directory to look for .cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

# Enable release build
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set directory to boost
SET(BOOST_ROOT "../../../Libraries/boost-1.64.0-win-x64")

# set Boost
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

# Include libraries
find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS chrono regex system serialization filesystem log thread REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)


# Set include folders
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${Boost_INCLUDE_DIRS}
                    ${GLEW_INCLUDE_DIRS}
                    ${GLUT_INCLUDE_DIRS}
                    ${GLM_INCLUDE_DIRS}
                    ${GLFW3_INCLUDE_DIRS})

# Add sources
file(GLOB_RECURSE SOURCES "*.cpp")
add_executable(occ-lesson01 ${SOURCES})

# Link libraries
target_link_libraries(occ-lesson01
    ${GLFW3_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${Boost_LIBRARIES}
    ${GLEW_LIBRARY})

# add Boost definition
add_definitions(-DBOOST_LOG_DYN_LINK)

# add Wno-literal-suffix to suppress warning messages
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")

###
# Installing
##
install (TARGETS occ-lesson01 DESTINATION bin)
