# set minimum cmake requirements
cmake_minimum_required(VERSION 3.5)
project (occ-lesson05)

# add custom directory to look for .cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

# Enable release build
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set directory to boost
if(WIN32)
SET(BOOST_ROOT "../vendor/boost-1.74.0-win-x64")
else()
add_definitions(-DEIGEN_NO_DEBUG -Wno-literal-suffix)
SET(BOOST_INCLUDEDIR "/usr/include")
SET(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
endif()

# set Boost
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)
set (Boost_NO_BOOST_CMAKE ON)

# Include libraries
find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS chrono regex system serialization filesystem log thread REQUIRED)
find_package(GLFW3 REQUIRED)
if(WIN32)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
else()
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW3 REQUIRED glfw3)
endif()


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
add_executable(occ-lesson05 ${SOURCES})

# Link libraries
target_link_libraries(occ-lesson05
    ${GLFW3_LIBRARIES}
    ${OPENGL_glu_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${Boost_LIBRARIES}
    ${GLEW_LIBRARIES})

# add Boost definition
add_definitions(-DBOOST_LOG_DYN_LINK)

# add Wno-literal-suffix to suppress warning messages
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")

###
# Installing
##
install (TARGETS occ-lesson05 DESTINATION bin)
